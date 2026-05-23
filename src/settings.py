# pyright: reportCallIssue=false

import os
from pathlib import Path

from pydantic import ConfigDict
from pydantic_settings import BaseSettings, SettingsConfigDict


class Settings(BaseSettings):
    """Configuration settings for the application."""

    base_dir: Path = Path(__file__).parent.parent
    cache_dir: Path = base_dir / '.cache'
    open_router_key: str
    open_router_model: str = 'openai/gpt-oss-120b:free'
    cache_file: str = 'cache.json'

    model_config = SettingsConfigDict(env_file=".env", env_file_encoding="utf-8")


settings = Settings()
