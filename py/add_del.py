from file import File, elem_create
from helper import *
import log
import os


def add_article(c_idx: int, e_idx: int, a_idx: int) -> None:
    path = File.rootdir
    category_suffix(path, c_idx)
    elem = File.data[c_idx][e_idx]

    if len(elem["content"] == 0):
        elem["content"].append("brief")
        path += f"/{elem['name']}/Brief.txt"
    else:
        name = f"Article_{len(elem['content'])}"

        if a_idx == -1:
            elem["content"].append(name)
        else:
            elem["content"].insert(a_idx, name)

        path += f"/{elem['name']}/{name}.txt"

    print(log.OutColor.GREEN, end='')
    #view_element(c_idx, e_idx)
    print(log.OutColor.RESET)

    open(path, 'w')
    
def del_article(c_idx: int, e_idx: int, a_idx: int) -> None:
    path = File.rootdir
    category_suffix(path, c_idx)
    elem = File.data[c_idx][e_idx]

    path += f"/{elem['name']}/{elem['content'][a_idx]}.txt"
    elem["content"].pop(a_idx)

    print(log.OutColor.RED, end='')
    #view_element(c_idx, e_idx)
    print(log.OutColor.RESET)

    os.remove(path)


def add_element(c_idx: int, e_idx: int, _: int) -> None:
    path = File.rootdir
    category_suffix(path, c_idx)

    print(len(File.data))
    print(c_idx)

    if e_idx == -1:
        File.data[c_idx].append(elem_create(c_idx))
    else:
        File.data[c_idx].insert(e_idx, elem_create(c_idx))

    path += '/' + File.data[c_idx][e_idx]["name"]
    os.mkdir(path)
    add_article(c_idx, e_idx, 0)

def del_element(c_idx: int, e_idx: int, _: int) -> None:
    path = File.rootdir
    category_suffix(path, c_idx)
    elem = File.data[c_idx]

    os.remove(path + elem[e_idx].name)
    File.data[c_idx].pop(e_idx)


def cmd_add(command: list[int | str]) -> bool:
    location = parse_loc_str(command, 1)
    if not location:
        return False

    if location["article"] == -2:
        add_element(*location.values())
    else:
        add_article(*location.values())

    print(log.OutColor.GREEN, end='')
    list_elements(location["category"])
    print(log.OutColor.RESET)
    
    return True

def cmd_del(command: list[int | str]) -> bool:
    location = parse_loc_str(command, 1)
    if not location:
        return False

    if location["article"] == -2:
        del_element(*location.values()[0:2])
    else:
        del_article(*location.values())

    print(log.OutColor.RED, end='')
    list_elements(location["category"])
    print(log.OutColor.RESET)
