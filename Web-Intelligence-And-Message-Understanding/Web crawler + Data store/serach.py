from elasticsearch import Elasticsearch
import json
from pathlib import Path
from datetime import date


ANS_DIR = "./answer"


def query(query):
    es = Elasticsearch()

    index_name = "wiki_qa_v2"
    type = "one_to_one"

    # Query DSL
    search_params = {
        "query": {"match": {"question": query}},
        "size": 2,
    }
    # Search document
    result = es.search(
        index=index_name, doc_type=type, body=search_params
    )
    result = result["hits"]["hits"][0]

    today = date.today()
    dt = today.strftime("%y-%m-%d-%H-%M-%S")
    with open(
        f"{ANS_DIR}/{dt}.json", "w", encoding="UTF-8"
    ) as f:
        result = json.dumps(result, indent=2)
        print(result)
        print(result, file=f)


if __name__ == "__main__":
    # create folder if not exist
    Path(ANS_DIR).mkdir(parents=True, exist_ok=True)

    query(input("請輸入您要查詢的關鍵字?"))
