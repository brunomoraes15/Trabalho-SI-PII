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
        
    def filter_data(self):
        filtered_data = []
        with open("data.csv", "r", encoding="utf-8") as data:
            for i in data:
                cleaned_line = re.sub(r"^\d+[\W\s]*", "", i).replace(",", "")
                filtered_data.append(cleaned_line)

        with open("data_fixed.csv", "w", encoding="utf-8") as new_file:
            new_file.write("".join(filtered_data))

    def collect_data(self):
        try:
            self.browser.get(self.url)
            try:
                
                print("we believed")
                raw_data_a = self.browser.find_element(By.XPATH, xpath_a).text
                raw_data_b = self.browser.find_element(By.XPATH, xpath_b).text

                self.save_data(raw_data_a, raw_data_b)
                self.filter_data()
                self.browser.quit()
                print("we'd catch the rainbow")

            except Exception as e:
                print(f"error while scrapping data {e}")

        except Exception as e:
            print(f"error while accessing the web page {e}")
            return None

 
if __name__ == "__main__":
    scrapper = ScrappingTool(website)
    scrapper.collect_data()