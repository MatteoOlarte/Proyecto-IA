import json

from openai import OpenAI
from openai.types.responses import Response, ResponseInputItemParam, ToolParam

from settings import settings
from trackers import APIUsageTracker
from utils import cop_to_usd, usd_to_cop

_tracker = APIUsageTracker()

_client = OpenAI(
    base_url='http://192.168.1.2:11434/v1',
    api_key='ollama',
)

_tools: list[ToolParam] = [
    {
        'type': 'function',
        'name': 'usd_to_cop',
        'description': 'Convierte un monto en dólares estadounidenses a pesos colombianos usando la tasa TRM actual.',
        'strict': True,
        'parameters': {
            'type': 'object',
            'properties': {
                'amount': {
                    'type': 'number',
                    'description': 'Monto en USD que se desea convertir.',
                },
                'replace_cache': {
                    'type': 'boolean',
                    'description': 'Indica si se debe ignorar la caché y consultar la TRM de nuevo.',
                },
            },
            'required': ['amount', 'replace_cache'],
            'additionalProperties': False,
        },
    },
    {
        'type': 'function',
        'name': 'cop_to_usd',
        'description': 'Convierte un monto en pesos colombianos a dólares estadounidenses usando la tasa TRM actual.',
        'strict': True,
        'parameters': {
            'type': 'object',
            'properties': {
                'amount': {
                    'type': 'number',
                    'description': 'Monto en COP que se desea convertir.',
                },
                'replace_cache': {
                    'type': 'boolean',
                    'description': 'Indica si se debe ignorar la caché y consultar la TRM de nuevo.',
                },
            },
            'required': ['amount', 'replace_cache'],
            'additionalProperties': False,
        },
    }
]

_sysprompts = 'You are a local IA assistant nammed Gemma. Your task is helping the user with any question and any task, reply them in the same language they ask you. '


def start_chat():
    print('Iniciando chat (escribe \'salir\' o \'quit\' para terminar).')

    messages: list[ResponseInputItemParam] = [
        {'role': 'system', 'content': _sysprompts},
    ]

    try:
        while True:
            user_input: str = input('Tú: ').strip()

            if user_input is None:
                continue

            if user_input.lower() in (r'\bye'):
                print('Cerrando chat.')
                break

            messages.append({'role': 'user', 'content': user_input})

            response = _client.responses.create(
                model='gemma4:e4b',
                tools=_tools,
                input=messages,
            )

            messages += response.output  # type: ignore

            while any(item.type == 'function_call' for item in response.output):
                for item in response.output:
                    if item.type != 'function_call':
                        continue

                    args = json.loads(item.arguments)

                    if item.name == 'usd_to_cop':
                        result = usd_to_cop(args['amount'], args['replace_cache'])
                    elif item.name == 'cop_to_usd':
                        result = cop_to_usd(args['amount'], args['replace_cache'])
                    else:
                        continue

                    messages.append({
                        'type': 'function_call_output',
                        'call_id': item.call_id,
                        'output': str(result),
                    })

                response = _client.responses.create(
                    model='gemma4:e4b',
                    tools=_tools,
                    input=messages,
                )

                messages.extend(response.output)  # type: ignore

            _tracker.add_response(response)
            _tracker.show()
    except KeyboardInterrupt:
        print('\nChat interrumpido por el usuario.')


def _check_function_calls(response: Response) -> bool:
    ...


start_chat()
