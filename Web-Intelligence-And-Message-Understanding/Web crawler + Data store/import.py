from elasticsearch import Elasticsearch, helpers
import json

from numpy import indices

DATA_FOLDER = "./data"
HASH_TABLE_FILE = "./hash_table.txt"
HASH_TABLE = []

qa_mapping = {
    "properties": {
        "url": {"type": "text"},
        "hash": {"type": "text"},
        "title": {"type": "keyword"},
        "content": {
            "type": "text",
            "analyzer": "ik_smart",
            "search_analyzer": "ik_max_word",
        },
    }
}


def read_data():
    try:
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

        for js_file in HASH_TABLE:
            with open(
                f"{DATA_FOLDER}/{js_file}.json",
                "r",
                encoding="UTF-8",
            ) as f:
                js = json.load(f)
            yield js

    except IOError:
        print("Please run crawler first~")
        exit()


def load2_elasticsearch():
    index_name = "wiki_qa_v2"
    type = "one_to_one"
    es = Elasticsearch()

    # Create index
    if not es.indices.exists(index=index_name):
        es.indices.create(index=index_name)
    print("Index created!")

    # Put mapping into index
    if not es.indices.exists_type(
        index=index_name, doc_type=type
    ):
        es.indices.put_mapping(
            index=index_name,
            doc_type=type,
            body=qa_mapping,
            include_type_name=True,
        )
    print("Mappings created!")

    # Import data to elasticsearch
    success, _ = helpers.bulk(
        client=es,
        actions=read_data(),
        index=index_name,
        doc_type=type,
        ignore=400,
    )
    print("success:", success)


if __name__ == "__main__":
    load2_elasticsearch()
