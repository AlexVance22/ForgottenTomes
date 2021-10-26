from file import File
import log


def parse_loc_str(command: list[str | int], idx: int) -> dict[str, int] | None:
    current = False
    location = {}

    match command[idx]:
        case '.':
            location = File.selected_loc()
            if location:
                current = True
            else:
                return None
        case ("session" | "ses"):
            location["category"] = 0
        case ("location" | "loc"):
            location["category"] = 1
        case ("character" | "cha"):
            location["category"] = 2
        case ("item" | "itm"):
            location["category"] = 3
        case _:
            log.err("Invalid item type")
            return None

    idx += 1

    if not current:
        if type(command[idx]) == int:
            location["element"] = command[idx]
        elif command[idx] == "end":
            location["element"] = -1
        else:
            log.err("Invalid index specifier")
            return None

        idx += 1

    if idx < len(command):
        if command[idx] == "article" or command[idx] == "art":
            idx += 1

            if type(command[idx]) == int:
                location["article"] = command[idx]
            elif command[idx] == "end":
                location["article"] = -1
            else:
                log.err("Invalid index specifier")
                return None
        else:
            log.err("Invalid trailing arguments")
            return None
    else:
        location["article"] = -2

    return location


def category_suffix(base: str, category: int) -> None:
    match category:
        case 0:
            base += "/sessions"
        case 1:
            base += "/locations"
        case 2:
            base += "/characters"
        case 3:
            base += "/items"


def print_file(file_path: str) -> None:
    with open(file_path) as f:
        print(f.read())


def list_elements(c_idx: int) -> None:
    match c_idx:
        case 0:
            print("Sessions----------------------------------\n")
        case 1:
            print("Locations---------------------------------\n")
        case 2:
            print("Characters--------------------------------\n")
        case 3:
            print("Items-------------------------------------\n")

    for i, item in enumerate(File.data[c_idx]):
        print(f"{i}: {item['name']}")

    print("\n------------------------------------------")


def view_element(c_idx: int, e_idx: int) -> None:
    elem = File.data[c_idx][e_idx]
    print(f"Name: {elem['name']} \n")

    for i, article in elem["content"]:
        print("-----------------------")
        print(i + " - " + article + "\n")
        path = File.rootdir
        category_suffix(path, c_idx)
        print_file(path, elem["name"] + '/' + article + ".txt")
