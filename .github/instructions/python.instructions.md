---
name: 'Python Standards'
applyTo: '**.{py,ipynb}'
description: 'Enforce Python 3.13 coding standards for all Python files and notebooks. Includes formatting, mandatory parameter type annotations, naming conventions, imports, and Spanish-language docstrings.'
---

# Python Standards

## Python Version

- Target runtime: Python 3.13
- Always use Python 3.13-compatible syntax and standard library features
- Prefer modern Python constructs over legacy alternatives

### Preferred Modern Syntax

Prefer:

```python
list[str]
dict[str, int]
Optional[str]
```

Instead of:

```python
List[str]
Dict[str, int]
Union[str, None]
```

- Prefer modern typing syntax when it improves readability
- Use built-in generic types whenever possible
- Prefer `Optional[T]` over `Union[T, None]`
- Avoid outdated compatibility patterns for older Python versions

---

# Code Style

## Formatting

- Follow PEP 8
- Use `isort` for import organization
- Indentation: 4 spaces
- Maximum line length: 200 characters

---

# String Style

- Prefer single quotes over double quotes

### Preferred

```python
status = 'active'
message = 'operation completed'
```

### Avoid

```python
status = "active"
message = "operation completed"
```

---

# Type Annotations

## Mandatory Parameter Type Annotations

ALL function and method parameters MUST include explicit type annotations.

This rule applies to:
- public functions
- private functions
- methods
- async functions
- nested functions
- class methods
- static methods

### Required

```python
def create_item(name: str, quantity: int, active: bool):
    ...
```

```python
async def fetch_data(url: str, timeout: int):
    ...
```

```python
def _map_items(items: list[str]):
    ...
```

### Forbidden

```python
def create_item(name, quantity, active):
    ...
```

```python
def fetch_data(url, timeout=30):
    ...
```

---

## Return Types

- Return type annotations are recommended but optional

### Preferred

```python
def get_item(item_id: int) -> Item:
    ...
```

### Allowed

```python
def get_item(item_id: int):
    ...
```

---

## Type Annotation Rules

- Prefer concrete types over `Any`
- Avoid unnecessary `Any`
- Use precise collection types
- Use custom types and aliases when they improve clarity
- Keep annotations readable and maintainable

---

# Trust Typed Objects and Type Hints

Typed values MUST be treated as trusted contracts.

If a variable, parameter, or attribute already has an explicit type annotation, do NOT add redundant defensive checks, runtime validation, fallback access patterns, or unnecessary type coercion.

This rule applies to:
- primitive types
- typed objects
- dataclasses
- Pydantic models
- DTOs
- entities
- typed collections

---

## Preferred

```python
def process_order(total: int):
    final_total = total
```

```python
def create_user(user_data: CreateUserSchema):
    email = user_data.email
    name = user_data.name
```

```python
def normalize_text(value: str):
    normalized = value.lower()
```

---

## Forbidden

```python
if isinstance(total, int):
    ...
```

```python
if isinstance(value, str):
    ...
```

```python
email = getattr(user_data, 'email', None)
```

```python
if hasattr(user_data, 'email'):
    ...
```

```python
email = user_data.model_dump().get('email')
```

```python
safe_total = int(total)
```

when `total` is already typed as `int`.

```python
safe_value = str(value)
```

when `value` is already typed as `str`.

---

# Avoid Redundant Validation

Do not re-validate data that has already been validated or typed.

### Forbidden

```python
validated = CreateUserSchema(**user_data.model_dump())
```

```python
validated = CreateUserSchema.model_validate(existing_model)
```

when `existing_model` is already validated.

---

# Prefer Direct Access Over Defensive Patterns

For typed objects:
- prefer direct attribute access
- prefer dot notation
- trust the declared contract
- avoid defensive access helpers

Do NOT use:
- `getattr`
- `hasattr`
- `.get()`
- dictionary-style access
- fallback defaults for required fields

unless the object is explicitly dynamic or untyped.

---

## Preferred

```python
item_id = payload.item_id
status = payload.status
value = payload.value
```

---

## Forbidden

```python
item_id = payload.get('item_id')
```

```python
status = payload['status']
```

```python
value = getattr(payload, 'value', None)
```

```python
if hasattr(payload, 'status'):
    ...
```

---

# Exception: Dynamic or Untyped Data

Defensive validation IS allowed when:
- the value is typed as `Any`
- the object is dynamic
- the source is external or untrusted
- runtime validation is explicitly required
- the value has no type annotation

### Allowed

```python
def process_data(data: Any):
    if isinstance(data, dict):
        ...
```

```python
payload = request.json()

if 'value' in payload:
    ...
```

---

# Imports

- Use absolute imports inside `src/`
- Use relative imports only for local module relationships when appropriate
- Place all imports at the top of the file
- Organize imports with `isort`

---

# Naming Conventions

## Variables

- Use `snake_case`
- Use descriptive and meaningful names
- Avoid abbreviations unless they are widely understood

### Preferred

```python
item_name = 'example'
total_items = 10
created_at = datetime.now()
```

### Allowed Exceptions

Loop counters:

```python
for i in items:
    ...
```

---

## Functions

- Use `snake_case`
- Use descriptive action-oriented names
- Internal helper functions should use `_` prefix

### Preferred

```python
def create_item():
    ...

def _validate_input():
    ...
```

---

## Methods

- Use `snake_case`
- Keep naming consistent with function naming rules

### Preferred

```python
class ItemService:

    def get_item_by_id(self, item_id: int):
        ...
```

---

## Classes

- Use `PascalCase`

### Preferred

```python
class ItemService:
    ...
```

---

## Constants

- Use `UPPER_SNAKE_CASE`

### Preferred

```python
MAX_RETRIES = 3
DEFAULT_TIMEOUT = 30
API_VERSION = 'v1'
```

---

## Types

- Use `PascalCase`

### Preferred

```python
type ItemId = int

class ItemResponse:
    ...
```

---

# Docstrings

## Language Rules

- Use clear and technical language
- Avoid conversational tone
- Keep descriptions concise and implementation-focused

---

# Standard Docstring Format

Public functions must include docstrings unless explicitly excluded below.

Private helper functions may omit docstrings when their behavior is self-explanatory.

```python
"""
Short one-line summary.

Args:
    param1 (type): Description of the parameter.
    param2 (type): Description of the parameter.

Returns:
    type: Description of the returned value.

Raises:
    ExceptionType: Description of the exception condition.
"""
```

## Docstring Rules

- The summary must be concise
- All parameters must be documented
- Always include `Returns`
- Include `Raises` only when applicable
- Avoid redundant explanations
- Describe behavior, not implementation details

---

# Special Rule: Use Case Files

For use case files:

- Only the main `invoke` function should contain a docstring
- Internal helper functions MUST NOT include docstrings

## invoke Format

```python
"""
Short summary of the use case.

Clear description of the functional purpose within the system.

Args:
    input_data (type): Data required by the use case.

Returns:
    type: Use case result.
"""
```

---

# Additional Engineering Rules

- Prefer meaningful English names for identifiers
- Avoid redundant comments
- Raise exceptions with informative messages
- Maintain consistency with existing project patterns
- Prefer readability over clever abstractions
- Avoid unnecessary complexity
```