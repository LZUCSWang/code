from selenium import webdriver
import time
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
import smtplib
from email.mime.text import MIMEText
from email.header import Header
from selenium import webdriver
from selenium.webdriver.firefox.options import Options as FirefoxOptions
import time
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
import smtplib
from email.mime.text import MIMEText
from email.header import Header
from pyvirtualdisplay import Display
import datetime
Location = [35.943360, 104.151292]

test_url = "https://docs.qq.com/form/page/DTWZOU1RoVFN5aXRM"
# url = 'https://docs.qq.com/form/page/DSkpjeURSQVVUS3hs'
url = "https://docs.qq.com/form/page/DTmRJQmlJZHpET0Zm"


def send_email(subject):
    subject = subject + url
    sender = "2949242759@qq.com"  # 发送邮箱
    receivers = ["1779222504@qq.com"]  # 接收邮箱
    auth_code = "pkyothtbwxzbdcdd"  # 授权码

    message = MIMEText("Python穉uto", "plain", "utf-8")
    message["From"] = Header("Sender<%s>" % sender)  # 发送者
    message["To"] = Header("Receiver<%s>" % receivers[0])  # 接收者

    # subject = 'Python SMTP 邮件测试'
    message["Subject"] = Header(subject, "utf-8")

    try:
        server = smtplib.SMTP_SSL("smtp.qq.com", 465)
        server.login(sender, auth_code)
        server.sendmail(sender, receivers, message.as_string())
        print("send successfully")
        server.close()
    except smtplib.SMTPException:
        print("Error: ")


def TargetWeb(url, user="WangXianyi"):
    try:                                
        profile = webdriver.FirefoxProfile('/root/.mozilla/firefox/1xwfl67f.default-release')
        browser = webdriver.Firefox(profile)
        browser.get(url)
        browser.implicitly_wait(10)
        time.sleep(10)  # 暂停3s
        browser.execute_script("navigator.geolocation.getCurrentPosition = function(success) { success({coords: {latitude: 35.943360, longitude: 104.151292}}); }")
        print("browser opeened",end='---')
    except Exception as e:
        print(e)
        print("browser error")
        quit()
    try:
        browser.find_element(By.XPATH, "//div[@class='location-btn']").click()  # 定位
    except:
        print("No location!")
        send_email("No location!")
        quit()
    print("Find location!",end='---')
    time.sleep(10)
    try:
        browser.find_element(By.XPATH, "//button[@type='button']").click()  # 提交
    except:
        print("No button!")
        send_email("No button!")
        quit()
    print("Find button!",end='---')
    time.sleep(10)
    try:
        browser.find_element(
            By.CSS_SELECTOR,
            "body > div.dui-modal-mask.dui-modal-mask-visible.dui-modal-mask-display > div > div.dui-modal-footer > button.dui-button.dui-modal-footer-ok.dui-button-type-primary.dui-button-size-default > div",
        ).click()
    except:
        print("No push!")
        send_email("No push!")
        quit()
    print("Find push!",end="---")
    time.sleep(3)
    print("Done!",end=f"------{datetime.date.today()}\n")


if __name__ == "__main__":
    print("Start",end="---")
    with Display(visible=False, size=(1200, 1500)):
        TargetWeb(url)

    # TargetWeb(url,"WangXianyi")
    #TargetWeb(test_url)
