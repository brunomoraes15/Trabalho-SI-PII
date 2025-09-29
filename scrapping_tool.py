from selenium.webdriver.common.by import By
from browser import start_browser
from config import *
import re, csv

class ScrappingTool:
    def __init__(self, url):
        self.url = url
        self.browser = start_browser()

    def save_data(self, data_a, data_b):
        try:
            with open("data.csv", "w", encoding="utf-8") as file:
                file.write(f"{data_a}\n{data_b}")
            pass

        except Exception as e:
            print(f"error while saving the data {e}")
            return None
        

    def collect_data(self):
        try:
            self.browser.get(self.url)
            try:
                
                print("we'd catch the rainbow")

                raw_data_a = self.browser.find_element(By.XPATH, xpath_a).text
                raw_data_b = self.browser.find_element(By.XPATH, xpath_b).text

                self.save_data(raw_data_a, raw_data_b)
                self.filter_data()
                self.browser.quit()

            except Exception as e:
                print(f"error while scrapping data {e}")

        except Exception as e:
            print(f"error while accessing the web page {e}")
            return None

 
if __name__ == "__main__":
    scrapper = ScrappingTool(website)
    scrapper.collect_data()