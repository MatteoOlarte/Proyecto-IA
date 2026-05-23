import json
import os
import re
from datetime import datetime, timedelta
from decimal import Decimal

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.ui import WebDriverWait

from settings import settings


def get_trm_value(replace: bool = False):
    cache = settings.cache_dir / 'trm_value.json'
    if os.path.exists(cache):
        with open(cache, "r") as f:
            cache = json.load(f)

        cached_at = datetime.fromisoformat(cache["cached_at"])
        if replace or datetime.now() - cached_at < timedelta(hours=24):
            return cache["value"]

    options = webdriver.ChromeOptions()
    driver = webdriver.Chrome(options=options)
    text_value = ''

    try:
        driver.get("https://www.banrep.gov.co/es/glosario/tasa-cambio-trm")
        element = WebDriverWait(driver, 10).until(
            EC.presence_of_element_located((By.CSS_SELECTOR, "div.indicator__value a"))
        )
        text_value = element.text.replace('.', '').replace(',', '.')

        os.makedirs(os.path.dirname(cache), exist_ok=True)

        with open(cache, "w") as f:
            json.dump({"value": text_value, "cached_at": datetime.now().isoformat()}, f)

        return text_value
    finally:
        driver.quit()


def usd_to_cop(amount: Decimal, replace_cache: bool = False) -> Decimal:
    trm_value = Decimal(get_trm_value(replace_cache))
    return amount * trm_value


def cop_to_usd(amount: Decimal, replace_cache: bool = False) -> Decimal:
    trm_value = Decimal(get_trm_value(replace_cache))
    return amount / trm_value
