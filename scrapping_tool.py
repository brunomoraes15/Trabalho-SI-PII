from selenium.webdriver.common.by import By
from browser import start_browser
from config import *

class ScrappingTool:
    def __init__(self, url):
        self.url = url
        self.browser = start_browser()
        
    def exit(self):
        self.browser.quit()
        
    def collect_data(self):
        try:
            self.browser.get(self.url)
            
            try:
                
                print("catch the rainbow")
                title_test = self.browser.find_element(By.XPATH, "/html/body/div[3]/div[2]/div[3]/div[4]/div[1]/div/div[1]/div[12]/div[1]/div")
                print(title_test.text)
                self.exit()

            except Exception as e:
                print(f"Erro ao acessar website {e}")

        except Exception as e:
            print(f"Erro ao acessar o navegador {e}")
            return None
        
if __name__ == "__main__":
    scrapper = ScrappingTool(website)
    scrapper.collect_data()