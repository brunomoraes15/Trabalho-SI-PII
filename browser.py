from selenium import webdriver
from selenium.webdriver.firefox.service import Service as FirefoxService
from selenium.webdriver.firefox.options import Options as FirefoxOptions
from webdriver_manager.firefox import GeckoDriverManager


def iniciar_browser():
    try:
        print("executando Firefox")
        firefox_options = FirefoxOptions()
        firefox_options.add_argument("--headless")  
        #firefox_options.add_argument("--disable-gpu") 

        service = FirefoxService(executable_path=GeckoDriverManager().install())
        driver = webdriver.Firefox(service=service, options=firefox_options)
        print("executando Firefox")
        return driver
        

    except Exception as e:
        print("Nenhum navegador encontrado no sistema.")
        print("Erro:", e)
        return None

iniciar_browser()