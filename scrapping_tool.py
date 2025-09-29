import re
import csv
from selenium.webdriver.common.by import By
from browser import start_browser
from config import *

class ScrapingTool:
    def __init__(self, url):
        self.url = url
        self.browser = start_browser()

    def save_data(self, data_a, data_b):
        try:
            
            with open("data.csv", "w", encoding="utf-8") as file:
                file.write(data_a.strip() + "\n")
                file.write(data_b.strip() + "\n")

        except Exception as e:
            print(f"Error while saving the data: {e}")

    def filter_data(self):
        filtered_data = []
        with open("data.csv", "r", encoding="utf-8") as data:
            for i in data:

                cell = re.sub(r"^\d+[\W\s]*", "", i).replace(",", "")
                filtered_data.append(cell.strip())

        with open("data_fixed.csv", "w", encoding="utf-8") as new_file:
            for i in filtered_data:
                new_file.write(i + "\n")


    def collect_data(self):
        try:
            self.browser.get(self.url)

            try:
                print("We believed")
                raw_data_a = self.browser.find_element(By.XPATH, xpath_a).text
                raw_data_b = self.browser.find_element(By.XPATH, xpath_b).text

                self.save_data(raw_data_a, raw_data_b)
                self.filter_data()
                print("We'd catch the rainbow")

            except Exception as e:
                print(f"Error while scraping data: {e}")

        except Exception as e:
            print(f"Error while accessing the web page: {e}")

        finally:
            self.browser.quit()

if __name__ == "__main__":
    scrapper = ScrapingTool(website)
    scrapper.collect_data()
