#!/usr/bin/env python3
# -c is new component -s is a new system --init gets the base of the system ecs.h ecs.c the folder structure and makefile

import argparse
from pathlib import Path
from urllib.request import urlopen

from templates import component_c, component_h, system_c, system_h

repo_url = "https://github.com/CommonDrum/squegee"
raw_base = "https://raw.githubusercontent.com/CommonDrum/squegee/main"

init_files = [
    "ecs/ecs.h",
    "ecs/ecs.c",
    "makefile",
]


def render(template, name):
    lower = name.lower()
    capital = lower[:1].upper() + lower[1:]
    return (template
            .replace("{{Component_name}}", capital)
            .replace("{{component_name}}", lower)
            .replace("{{System_name}}", capital)
            .replace("{{system_name}}", lower))


def write(path, content):
    path = Path(path)
    if path.exists():
        print(f"skip (exists): {path}")
        return
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(content)
    print(f"created: {path}")


def fetch(relpath):
    url = f"{raw_base}/{relpath}"
    with urlopen(url) as r:
        return r.read().decode("utf-8")


def init_project():
    for f in init_files:
        write(f, fetch(f))
    Path("ecs/components").mkdir(parents=True, exist_ok=True)
    Path("ecs/systems").mkdir(parents=True, exist_ok=True)
    Path("src").mkdir(parents=True, exist_ok=True)


def new_component(name):
    lower = name.lower()
    folder = Path("ecs/components") / lower
    write(folder / f"{lower}.h", render(component_h, name).lstrip())
    write(folder / f"{lower}.c", render(component_c, name).lstrip())


def new_system(name):
    lower = name.lower()
    folder = Path("ecs/systems") / lower
    write(folder / f"{lower}.h", render(system_h, name).lstrip())
    write(folder / f"{lower}.c", render(system_c, name).lstrip())


def main():
    parser = argparse.ArgumentParser(prog="sqeg", description="squegee ECS tool")
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("--init", action="store_true", help="scaffold ecs/, src/, makefile from " + repo_url)
    group.add_argument("-c", metavar="NAME", help="create a new component")
    group.add_argument("-s", metavar="NAME", help="create a new system")
    args = parser.parse_args()

    if args.init:
        init_project()
    elif args.c:
        new_component(args.c)
    elif args.s:
        new_system(args.s)


if __name__ == "__main__":
    main()
