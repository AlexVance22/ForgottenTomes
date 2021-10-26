from types import new_class
from add_del import cmd_add, cmd_del
from help import cmd_help
from file import File
import tkinter as tk
from tkinter import filedialog
import log
import sys
import os


def cmd_list(command: list[int | str]):
    pass

def cmd_select(command: list[int | str]):
    pass

def cmd_view(command: list[int | str]):
    pass

def cmd_lookup(command: list[int | str]):
    pass

def cmd_edit(command: list[int | str]):
    pass

def cmd_rename(command: list[int | str]):
    pass

def cmd_create() -> bool:
    root = tk.Tk()
    # root.withdraw()
    rootdir = filedialog.asksaveasfilename()
    if not rootdir:
        return False
    
    rootdir = str(rootdir)

    os.mkdir(rootdir)
    os.mkdir(rootdir + "/sessions")
    os.mkdir(rootdir + "/locations")
    os.mkdir(rootdir + "/characters")
    os.mkdir(rootdir + "/items")

    with open(rootdir + "/camp.ft", 'w') as f:
        f.write('{"sessions":[],"locations":[],"characters":[],"items":[]}')

    File.reset()
    File.rootdir = rootdir
    File.filepath = rootdir + "/camp.ft"

    return True

def cmd_open() -> bool:
    root = tk.Tk()
    # root.withdraw()
    filepath = filedialog.askopenfilename()
    if not filepath:
        return False
    
    filepath = str(filepath)

    File.load(filepath)

    return True


def main():
    is_open = False

    while True:
        command: list[int | str] = [int(cmd) if cmd.isdigit() else cmd for cmd in input('>').split()]

        if len(command) == 0:
            log.err("Empty command")
            continue

        # os.system("CLS")

        if not is_open:
            match command[0]:
                case "new":
                    if cmd_create():
                        is_open = True
                case "open":
                    if cmd_open():
                        is_open = True
                case "help":
                    cmd_help()
                case "exit":
                    sys.exit()
                case _:
                    log.err("No file open")
        else:
            match command[0]:
                case "add":
                    if cmd_add(command):
                        File.save()
                case "del":
                    if cmd_del(command):
                        File.save()
                case "list":
                    cmd_list(command)
                case "select":
                    cmd_select(command)
                case "view":
                    cmd_view(command)
                case "lookup":
                    cmd_lookup(command)
                case "edit":
                    cmd_edit(command)
                case "rename":
                    if cmd_rename(command):
                        File.save()
                case "new":
                    if cmd_create():
                        is_open = True
                case "open":
                    if cmd_open():
                        is_open = True
                case "help":
                    cmd_help()
                case "exit":
                    sys.exit()
                case _:
                    log.err("Invalid command")


if __name__ == "__main__":
    main()
