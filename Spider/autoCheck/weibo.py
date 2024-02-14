import datetime
from email.header import Header
from email.mime.text import MIMEText
import smtplib
from selenium import webdriver
import time
from selenium.webdriver.common.keys import Keys
# 地理位置  经纬度
Location = [35.947357, 104.154051]  # 夏专 18#


url = 'https://weibo.com/u/6421538934'

# 导入日期包
# 获取当前日期
today = datetime.date.today()
begin = datetime.date(2023, 12, 4)
print()


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
    option.add_argument(
        r'--user-data-dir=C:\\Users\\wxy43\AppData\\Local\\Google\\Chrome\\User Data')  # 设置自己的浏览器数据路径
    option.add_argument(
        "user-agent='Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36'")
    option.add_experimental_option('excludeSwitches', ['enable-automation'])
    option.add_experimental_option('useAutomationExtension', False)
    # option.add_argument('--headless')
    # option.add_argument('--no-sandbox')
    option.add_argument('--disable-gpu')

    # 指定ChromeDriver的路径
    chrome_driver_path = r'C:\\Users\wxy43\AppData\\Local\\Google\\Chrome\Application\\chromedriver.exe'
    browser = webdriver.Chrome(
        executable_path=chrome_driver_path, options=option)
    browser.execute_cdp_cmd("Page.addScriptToEvaluateOnNewDocument", {
        "source": """
        Object.defineProperty(navigator, 'webdriver', {
        get: () => undefined
        })
    """
    })
    browser.set_window_size(1920, 1050)
    browser.execute_cdp_cmd("Emulation.setGeolocationOverride", {
        "latitude": Location[0],
        "longitude": Location[1],
        "accuracy": 100
    })
    browser.get(url)
    browser.implicitly_wait(10)
    time.sleep(2)  # 暂停3s
    browser.find_element_by_css_selector(
        "#scroller > div.vue-recycle-scroller__item-wrapper > div:nth-child(1) > div > article > footer > div > div > div > div:nth-child(1) > div > div > span > div").click()
    print("单击转发成功")
    time.sleep(0.5)
    browser.find_element_by_css_selector(
        "#scroller > div.vue-recycle-scroller__item-wrapper > div:nth-child(1) > div > article > footer > div > div > div > div:nth-child(1) > div > div > div > div > div:nth-child(2)").click()
    time.sleep(1)
    browser.find_element_by_css_selector(
        "#scroller > div.vue-recycle-scroller__item-wrapper > div:nth-child(1) > div > article > div:nth-child(3) > div.Feed_box_3fswx > div.woo-box-flex.Feed_mar2_3L-z0 > div.woo-box-item-flex > div > div:nth-child(1) > div > textarea").send_keys(Keys.CONTROL, 'a')
    time.sleep(2)
    browser.find_element_by_css_selector(
        "#scroller > div.vue-recycle-scroller__item-wrapper > div:nth-child(1) > div > article > div:nth-child(3) > div.Feed_box_3fswx > div.woo-box-flex.Feed_mar2_3L-z0 > div.woo-box-item-flex > div > div:nth-child(1) > div > textarea").send_keys("第", (today-begin).days+1, "天")
    time.sleep(0.5)
    browser.find_element_by_css_selector(
        "#scroller > div.vue-recycle-scroller__item-wrapper > div:nth-child(1) > div > article > div:nth-child(3) > div.Feed_box_3fswx > div.woo-box-flex.Feed_mar2_3L-z0 > div.woo-box-item-flex > div > div.Composer_mar1_ujs0j > div > button").click()
    time.sleep(3)
    browser.refresh()
    print("转发成功")
    send_email("签到成功")

if __name__ == "__main__":
    print("开始执行")
    TargetWeb(url)
    # send_email("签到成功")