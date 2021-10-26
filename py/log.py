class OutColor:
    RED = "\033[91m"
    GREEN = "\033[92m"
    YELLOW = "\033[93m"
    BLUE = "\033[94m"
    CYAN = "\033[96m"
    RESET = "\033[0m"


def err(message: str) -> None:
    print(f"{OutColor.RED}--------------------\n\nERROR: {message} \n\n--------------------{OutColor.RESET}")