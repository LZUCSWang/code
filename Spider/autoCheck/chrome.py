from selenium import webdriver

option = webdriver.ChromeOptions()
option.add_argument(r'--user-data-dir=C:\\Users\\wxy43\AppData\\Local\\Google\\Chrome\\User Data')
option.add_experimental_option('excludeSwitches', ['enable-automation'])
driver = webdriver.Chrome(options=option)
url = 'https://docs.qq.com/form/page/DSkpjeURSQVVUS3hs'
test_url = 'https://docs.qq.com/form/page/DTWZOU1RoVFN5aXRM'
driver.get(test_url)
driver.find_element_by_xpath("//div[@class='location-btn']").click()   #selenium实现自动登录
