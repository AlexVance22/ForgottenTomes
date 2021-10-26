from typing import Any, Optional
import json
import log


def elem_create(category: int) -> dict[str, int | str | list[str]]:
    elem = { "type": 0, "number": elem_create.count[category] + 1, "relevance": 0, "name": "", "content": [] }
    elem_create.count[category] += 1
    return elem

elem_create.count = [0, 0, 0, 0]


class File:
    data: list[list[dict[str, int | str | list[str]]]] = [[], [], [], []]
    selected = { "category": -1, "element": -1, "article": -1 }
    filepath: str = ""
    rootdir: str = ""

    @classmethod
    def selected_loc(cls) -> Optional[dict[str, int]]:
        if File.selected["category"] != -1 and File.selected["item"] != -1:
            return cls.selected
        else:
            log.err("No item selected")
            return None

    @classmethod
    def save(cls, filepath: str = ""):
        if len(filepath) > 0:
            with open(filepath, 'w') as f:
                json.dump(cls.data, f)
                cls.filepath = filepath
                cls.rootdir = filepath.removesuffix("/camp.ft")
        else:
            with open(cls.filepath, 'w') as f:
                json.dump(cls.data, f)

    @classmethod
    def load(cls, filepath: str):
        with open(filepath, 'r') as f:
            cls.data = json.load(f)

    @classmethod
    def reset(cls):
        cls.data = [[], [], [], []]
        cls.selected = { "category": -1, "element": -1, "article": -1 }
        cls.filepath = ""
        cls.rootdir = ""

    @classmethod
    def fetch_category(cls, location: dict[str, int]) -> list[dict[str, Any]]:
        if location["category"] != -1:
            return cls.data[location["category"]]

    @classmethod
    def fetch_element(cls, location: dict[str, int]) -> dict[str, Any]:
        temp = cls.fetch_category()
        if location["element"] != -1:
            return temp[location["element"]]

    @classmethod
    def fetch_article(cls, location: dict[str, int]) -> list[tuple[str, str]]:
        temp = cls.fetch_element()
        if location["article"] != -1:
            return temp["content"][location["article"]]
