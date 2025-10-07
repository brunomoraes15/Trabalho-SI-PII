from selenium import webdriver
from selenium.webdriver.firefox.service import Service as FirefoxService
from selenium.webdriver.firefox.options import Options as FirefoxOptions
from webdriver_manager.firefox import GeckoDriverManager

def start_browser():
    try:
        options = FirefoxOptions()
        options.add_argument("--headless")  

        service = FirefoxService(executable_path=GeckoDriverManager().install())
        print('launching firefox...')
        driver = webdriver.Firefox(service=service, options=options)
        return driver
    
    except Exception as e:
        print("could not start web browser")
        print("error:", e)
        return None
