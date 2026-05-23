"""Módulo para el seguimiento de respuestas y uso de la API OpenAI."""

from openai.types.responses import Response
from rich.console import Console


class APIUsageTracker:
    """Clase para rastrear el uso de tokens y costos de la API."""

    def __init__(self) -> None:
        """Inicializa el tracker de uso de API."""
        self.prompt_tokens: int = 0
        self.output_tokens: int = 0
        self.total_tokens: int = 0
        self.total_cost: float = 0.0
        self.responses: list[Response] = []
        self._console = Console()

    @property
    def current_response(self):
        return self.responses[-1]

    def add_response(self, response: Response) -> None:
        """Agrega una respuesta del API al tracker.

        Args:
            response: Respuesta del API a agregar al tracker.
        """
        self.responses.append(response)
        usage = response.usage

        if usage is None:
            return

        self.prompt_tokens += usage.input_tokens
        self.output_tokens += usage.output_tokens
        self.total_tokens += usage.input_tokens + usage.output_tokens

    def get_last_response(self) -> Response | None:
        """Retorna la última respuesta agregada (FILO) sin removerla.

        Returns:
            La respuesta más reciente, o None si la pila está vacía.
        """
        return self.responses[-1] if self.responses else None

    def pop_response(self) -> Response | None:
        """Extrae y retorna la última respuesta agregada (FILO).

        Returns:
            La respuesta más reciente removida de la pila, o None si está vacía.
        """
        return self.responses.pop() if self.responses else None

    def get_summary(self) -> dict[str, int | float]:
        """Obtiene un resumen del uso de tokens y costos.

        Returns:
            Diccionario con el resumen del uso.
        """
        return {
            "input_tokens": self.prompt_tokens,
            "output_tokens": self.output_tokens,
            "total_tokens": self.total_tokens,
            "total_cost": self.total_cost,
        }

    def show(self) -> None:
        """Muestra información de la última respuesta en la consola."""
        last = self.get_last_response()

        if last is None:
            self._console.print("No response available", style="red")
            return

        response_text = last.output_text or str(last)
        self._console.print(response_text)
        self._console.print(f"(Tokens: {self.total_tokens})", justify="left", style="cyan")

    def __str__(self) -> str:
        """Devuelve una representación en cadena del estado del tracker."""
        return (
            f"Tokens tracker - Entrada: {self.prompt_tokens}, Salida: {self.output_tokens}, "
            f"Total: {self.total_tokens}, Costo: {self.total_cost}"
        )
