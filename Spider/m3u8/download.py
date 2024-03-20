import aiohttp
import asyncio
import os

async def download_ts_file(ts_url, ts_file_path):
    # 防止ssl报错：
    # aiohttp.client_exceptions.ClientConnectorCertificateError: Cannot connect to host ***.****.com:443 ssl:True
    # [SSLCertVerificationError: (1, '[SSL: CERTIFICATE_VERIFY_FAILED] certificate verify failed: unable to get local
    # issuer certificate (_ssl.c:1123)')]
    conn = aiohttp.TCPConnector(ssl=False)
    async with aiohttp.ClientSession(connector=conn) as session:
        async with session.get(ts_url) as response:
            if response.status != 200:
                print(f'{ts_url} 下载失败')
                return False
            with open(ts_file_path, 'wb') as f:
                while True:
                    chunk = await response.content.read(1024)
                    if not chunk:
                        break
                    f.write(chunk)
    print(f'{ts_url} 下载完成')
    return True

async def download_m3u8_video(url, file_path):
    # 防止ssl报错
    conn = aiohttp.TCPConnector(ssl=False)
    async with aiohttp.ClientSession(connector=conn) as session:
        async with session.get(url) as response:
            if response.status != 200:
                print('m3u8视频下载链接无效')
                return False

            m3u8_text = await response.text()
            m3u8_list = m3u8_text.split('\n')
            m3u8_list = [i for i in m3u8_list if i and i[0] != '#']

            tasks = []
            for i, ts_url in enumerate(m3u8_list):
                ts_url = url.rsplit('/', 1)[0] + '/' + ts_url
                ts_file_path = file_path.rsplit('.', 1)[0] + f'_{i}.ts'
                task = asyncio.ensure_future(
                    download_ts_file(ts_url, ts_file_path))
                tasks.append(task)

            await asyncio.gather(*tasks)

    print('m3u8视频下载完成')
    return True

def convert_ts_to_mp4(ts_file_path, mp4_file_path):
    os.system(f'ffmpeg -i {ts_file_path} -c copy {mp4_file_path}')

if __name__ == '__main__':
    url = 'https://player.ok123player.com/player/?url=https:\/\/www.51player1.com\/202207\/09\/RvkjT8Da\/index.m3u8'
    ts_file_path = 'E:\\ts'
    mp4_file_path = 'E:\\m3u8'

    loop = asyncio.get_event_loop()
    loop.run_until_complete(download_m3u8_video(url, ts_file_path))
    convert_ts_to_mp4(ts_file_path, mp4_file_path)
