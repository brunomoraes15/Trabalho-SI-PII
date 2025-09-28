from selenium.webdriver.common.by import By
from browser import start_browser
from config import *

class ScrappingTool:
    def __init__(self, url):
        self.url = url
        self.browser = start_browser()


    def save_data(self, data):
        try:
            with open("data.csv", "w", encoding="utf-8") as file:
                file.write(data)

            pass

        except Exception as e:
            print(f"error while saving the data {e}")
            return None
        
    def collect_data(self):
        try:
            self.browser.get(self.url)
            
            try:
                
                print("catch the rainbow")

                content_a = self.browser.find_element(By.XPATH, xpath_a)
                #print(content_a.text)
                raw_data = content_a.text

                content_b = self.browser.find_element(By.XPATH, xpath_b)
                #print(content_b.text)
                raw_data += content_b.text

                self.save_data(raw_data)
                self.browser.quit()
                

            except Exception as e:
                print(f"error while accessing the web page {e}")

        except Exception as e:
            print(f"error while accessing the web browser {e}")
            return None

    
        
if __name__ == "__main__":
    scrapper = ScrappingTool(website)
    scrapper.collect_data()