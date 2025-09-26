from selenium.webdriver.common.by import By
from browser import start_browser
#from config import *

class Scrapper:
    def __init__(self, url):
        self.url = url
        self.browser = start_browser()
        
    def exit(self):
        self.browser.quit()
        
    def collect_data(self):
        try:
            self.browser.get(self.url)
            
            try:
                pass
            #catch the rainbow

            except Exception as e:
                print(f"Erro ao acessar website {e}")

        except Exception as e:
            print(f"Erro ao acessar o navegador {e}")
            return None