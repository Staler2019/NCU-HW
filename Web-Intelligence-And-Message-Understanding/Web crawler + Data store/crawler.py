from bs4 import BeautifulSoup
import time
import requests
from pathlib import Path
import hashlib

TIME_WAITING_PERIOD = 1
DATA_FOLDER = "./data"
HASH_TABLE_FILE = "./hash_table.txt"


def crawler_each():
    # random a page
    resp = to_url(
        "https://zh.wikipedia.org/wiki/Special:%E9%9A%8F%E6%9C%BA%E9%A1%B5%E9%9D%A2"
    )
    # redirect to page in "台灣正體"
    url = resp.url
    new_url_tmp = url.split("/")
    new_url_tmp[3] = "zh-tw"
    new_url = new_url_tmp[0]
    for i in range(1, len(new_url_tmp)):
        new_url = new_url + "/" + new_url_tmp[i]

    time.sleep(TIME_WAITING_PERIOD)
    resp = to_url(new_url)

    js = parse(resp)
    write_json_to_file(js)


def to_url(url):
    resp = requests.get(
        url=url,
        verify=True,
        timeout=3,
    )
    if resp.status_code != 200:
        print("Invalid url:", resp.url)
    return resp


def remove_edit_btn(text):  # remove '[編輯]'
    return text[:-4]


def inner_breakable(soup_item):
    # break point: find "參考" or "連結" in h2
    if soup_item.name == "h2" and (
        "參考" in soup_item.text or "連結" in soup_item.text
    ):
        return True
    return False


def inner_continuable(soup_item):
    # None this item
    if soup_item.name is None:
        return True
    elif soup_item.name == "style":
        return True
    # tables
    elif soup_item.name == "table":
        return True
    # elif (
    #     soup_item.name == "table"
    #     and soup_item["class"]
    #     == "mbox-small plainlinks sistersitebox"
    # ):
    #     return True
    elif soup_item.find("div", {"class": "toctitle"}):
        return True
    # 數學會有亂碼
    elif soup_item.find(
        "span", {"class": "mwe-math-element"}
    ):
        return True
    return False


def write_json_to_file(js):
    with open(
        f"{DATA_FOLDER}/{js['hash']}.json",
        "w",
        encoding="UTF-8",
    ) as f:
        print(js, file=f)

    if js["hash"] not in HASH_TABLE:
        HASH_TABLE.append(js["hash"])

        # hash_table
        with open(
            HASH_TABLE_FILE, "a", encoding="UTF-8"
        ) as f:
            print(js["hash"], file=f)


def parse(resp):
    # use bs4 to see parser html
    url = resp.url

    soup = BeautifulSoup(resp.text, "html.parser")

    # title
    title = soup.h1.text
    print(title)
    # get sha256
    sha_obj = hashlib.sha256()
    sha_obj.update(title.encode("utf-8"))
    sha = sha_obj.hexdigest()

    # inner text
    content = ""
    my_text = soup.find(
        "div", {"class": "mw-parser-output"}
    )
    for my_tt in my_text:
        if inner_continuable(my_tt):
            continue
        if inner_breakable(my_tt):
            break

        if (
            my_tt.name == "h2"
            or my_tt.name == "h3"
            or my_tt.name == "h4"
            or my_tt.name == "h5"
            or my_tt.name == "h6"
        ):
            content = content + remove_edit_btn(my_tt.text)
        else:
            content = content + my_tt.text

    _json = {
        "url": url,
        "hash": sha,
        "title": title,
        "content": content,
    }

    return _json


def crawler(times):
    for i in range(times):
        print(i, end=" ")
        crawler_each()
        time.sleep(TIME_WAITING_PERIOD - 0.5)
        if i % 4 == 0:
            time.sleep(2)


if __name__ == "__main__":
    # create folder if not exist
    Path(DATA_FOLDER).mkdir(parents=True, exist_ok=True)

    HASH_TABLE = []
    try:
        # read hash table file
        with open(
            HASH_TABLE_FILE, "r", encoding="UTF-8"
        ) as f:
            HASH_TABLE = [
                line[:-1] for line in f.readlines()
            ]
            print(
                "Found {} data in history".format(
                    len(HASH_TABLE)
                )
            )
    except IOError:
        print(
            f"{HASH_TABLE_FILE} is not exist! Then it will be created this time. "
        )

    crawler(times=10000)
