from selenium import webdriver
import time
from selenium.webdriver.common.keys import Keys
# 地理位置  经纬度
Location = [35.947357, 104.154051]  # 夏专 18#

import smtplib
from email.mime.text import MIMEText
from email.header import Header
test_url = 'https://docs.qq.com/form/page/DTWZOU1RoVFN5aXRM'  # 测试用链接
url = 'https://docs.qq.com/form/page/DSkpjeURSQVVUS3hs'
def send_email(subject):
        
    sender = '2949242759@qq.com'  # 发送邮箱
    receivers = ['1779222504@qq.com']  # 接收邮箱
    auth_code = "phkgnsmrbfckdfbh"  # 授权码

    message = MIMEText('Python发送邮件', 'plain', 'utf-8')
    message['From'] = Header("Sender<%s>" % sender)  # 发送者
    message['To'] = Header("Receiver<%s>" % receivers[0])  # 接收者

    # subject = 'Python SMTP 邮件测试'
    message['Subject'] = Header(subject, 'utf-8')

    try:
        server = smtplib.SMTP_SSL('smtp.qq.com', 465)
        server.login(sender, auth_code)
        server.sendmail(sender, receivers, message.as_string())
        print("邮件发送成功")
        server.close()
    except smtplib.SMTPException:
        print("Error: 无法发送邮件")
def TargetWeb(url):
    option = webdriver.ChromeOptions()
    # option.binary_location = r'D:\\chrome-win64\\chrome.exe'
    option.add_argument(
        r'--user-data-dir=C:\\Users\\wxy43\AppData\\Local\\Google\\Chrome\\User Data')  # 设置自己的浏览器数据路径
    option.add_argument(
        "user-agent='Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36'")
    option.add_experimental_option('excludeSwitches', ['enable-automation'])
    option.add_experimental_option('useAutomationExtension', False)
<<<<<<< HEAD
    # option.add_argument('--headless')
    # option.add_argument('--no-sandbox')
    option.add_argument('--disable-gpu')
    # option.add_argument('--disable-dev-shm-usage')

    # 指定ChromeDriver的路径
    chrome_driver_path = r'C:\\Users\wxy43\AppData\\Local\\Google\\Chrome\Application\\chromedriver.exe'
    browser = webdriver.Chrome(executable_path=chrome_driver_path,options=option)
    browser.execute_cdp_cmd("Page.addScriptToEvaluateOnNewDocument", {
    "source": """
        Object.defineProperty(navigator, 'webdriver', {
        get: () => undefined
        })
    """
    })
    browser.set_window_size(1920,1050)
=======
    # option.add_argument("headless")
    # option.add_argument('--no-sandbox')
    # option.add_argument('--disable-gpu')
    # option.add_argument('--disable-dev-shm-usage')

    browser = webdriver.Chrome(options=option)
    browser.set_window_size(1000, 1000)
>>>>>>> 49c4a71e4177a62bcfec99ea70ea85a9f307e999
    browser.execute_cdp_cmd("Emulation.setGeolocationOverride", {
        "latitude": Location[0],
        "longitude": Location[1],
        "accuracy": 100
    })
    browser.get(url)
    browser.implicitly_wait(10)
    time.sleep(2)  # 暂停3s
    # browser.minimize_window()  # 浏览器最小化显示
    try:
        browser.find_element_by_xpath("//div[@class='location-btn']").click()  # 定位
    except:
        print("失败！定位不到‘定位’按钮")
        send_email("失败！定位不到‘定位’按钮")
        quit()
    print("单击定位按钮成功")
    time.sleep(1)
    try:
        browser.find_element_by_xpath("//button[@type='button']").click()  # 提交
    except:
        print("失败！定位不到‘提交’按钮")
        send_email("失败！定位不到‘提交’按钮")
        quit()
    print("单击提交按钮成功")
    time.sleep(1)
    try:
        browser.find_element_by_css_selector("body > div.dui-modal-mask.dui-modal-mask-visible.dui-modal-mask-display > div > div.dui-modal-footer > button.dui-button.dui-modal-footer-ok.dui-button-type-primary.dui-button-size-default > div").click()
    except:
        print("失败！定位不到‘确认’按钮")
        send_email("失败！定位不到‘确认’按钮")
        quit()
    print("单击确认按钮成功")
    time.sleep(3)
    print("签到成功")
    send_email("签到成功")

if __name__ == "__main__":
    print("开始执行")

    TargetWeb(url)
    # TargetWeb(test_url)