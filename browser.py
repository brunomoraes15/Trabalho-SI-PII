from selenium import webdriver
from selenium.webdriver.firefox.service import Service as FirefoxService
from selenium.webdriver.firefox.options import Options as FirefoxOptions
from webdriver_manager.firefox import GeckoDriverManager

def start_browser():
    try:
        print('starting browser')
        options = FirefoxOptions()
        print('setting up headless mode')
        options.add_argument("--headless")  

        print('gathering service via GeckoDriverManager')
        service = FirefoxService(executable_path=GeckoDriverManager().install())
        print('Launching Firefox...')
        driver = webdriver.Firefox(service=service, options=options)
        return driver
    
    except Exception as e:
        print("Could not start web browser")
        print("Error:", e)
        return None
