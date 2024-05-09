from selenium import webdriver
import time
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
import smtplib
from email.mime.text import MIMEText
from email.header import Header

# 地理位置  经纬度
Location = [35.943360, 104.151292]  # 夏专 3#

test_url = "https://docs.qq.com/form/page/DTWZOU1RoVFN5aXRM"  # 测试用链接
# url = 'https://docs.qq.com/form/page/DSkpjeURSQVVUS3hs'
url = "https://docs.qq.com/form/page/DTmRJQmlJZHpET0Zm"


def send_email(subject):
    subject = subject + url
    sender = "2949242759@qq.com"  # 发送邮箱
    receivers = ["1779222504@qq.com"]  # 接收邮箱
    auth_code = "pkyothtbwxzbdcdd"  # 授权码

    message = MIMEText("Python发送邮件", "plain", "utf-8")
    message["From"] = Header("Sender<%s>" % sender)  # 发送者
    message["To"] = Header("Receiver<%s>" % receivers[0])  # 接收者

    # subject = 'Python SMTP 邮件测试'
    message["Subject"] = Header(subject, "utf-8")

    try:
        server = smtplib.SMTP_SSL("smtp.qq.com", 465)
        server.login(sender, auth_code)
        server.sendmail(sender, receivers, message.as_string())
        print("邮件发送成功")
        server.close()
    except smtplib.SMTPException:
        print("Error: 无法发送邮件")


def TargetWeb(url, user="WangXianyi"):
    try:
        option = webdriver.ChromeOptions()
        user_data_dir = (
            "--user-data-dir=C:\\Users\\Administrator\AppData\\Local\\Google\\Chrome\\"
            + user
        )
        option.add_argument(user_data_dir)  # 设置自己的浏览器数据路径
        option.add_argument(
            "user-agent='Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36'"
        )
        option.add_experimental_option("excludeSwitches", ["enable-automation"])
        option.add_experimental_option("useAutomationExtension", False)
        option.add_argument("--disable-gpu")

        # 指定ChromeDriver的路径
        browser = webdriver.Chrome(options=option)
        browser.execute_cdp_cmd(
            "Page.addScriptToEvaluateOnNewDocument",
            {
                "source": """
            Object.defineProperty(navigator, 'webdriver', {
            get: () => undefined
            })
        """
            },
        )
        browser.set_window_size(1920, 1050)
        browser.execute_cdp_cmd(
            "Emulation.setGeolocationOverride",
            {"latitude": Location[0], "longitude": Location[1], "accuracy": 100},
        )
        browser.get(url)
    except:
        print("失败！浏览器打开错误")
        send_email("失败！浏览器打开错误")
        quit()
    print("浏览器打开成功")
    browser.implicitly_wait(10)
    time.sleep(10)  # 暂停3s
    try:
        browser.find_element(By.XPATH, "//div[@class='location-btn']").click()  # 定位
    except:
        print("失败！定位不到‘定位’按钮")
        send_email("失败！定位不到‘定位’按钮")
        quit()
    print("单击定位按钮成功")
    time.sleep(10)
    try:
        browser.find_element(By.XPATH, "//button[@type='button']").click()  # 提交
    except:
        print("失败！定位不到‘提交’按钮")
        send_email("失败！定位不到‘提交’按钮")
        quit()
    print("单击提交按钮成功")
    time.sleep(10)
    try:
        browser.find_element(
            By.CSS_SELECTOR,
            "body > div.dui-modal-mask.dui-modal-mask-visible.dui-modal-mask-display > div > div.dui-modal-footer > button.dui-button.dui-modal-footer-ok.dui-button-type-primary.dui-button-size-default > div",
        ).click()
    except:
        print("失败！定位不到‘确认’按钮")
        send_email("失败！定位不到‘确认’按钮")
        quit()
    print("单击确认按钮成功")
    time.sleep(3)
    print("签到成功")


if __name__ == "__main__":
    print("开始执行")
    TargetWeb(url,"WangXianyi")
    # TargetWeb(test_url)
