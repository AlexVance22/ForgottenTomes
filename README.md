# Lost Tomes
Command line tool to help me write my Dungeons and Dragons games. While this app was originally concieved for the purpose of running tabletop RPGs, it is now far more matured and well fitted out for any type worldbuilding scenario.

## What it does
It's a simple interface for organising and tracking notes. It was built out of a frustration I had with common popular tools such as world anvil or other tools that I always had difficulty explaining, but which essentially boiled down to feeling my creativity sapped by being given far too many templates and prescribed structures. What I really needed was just a simple way to keep track of basic hierarchies, categories and relations between various fragments and notes and nothing more, which ended up being almost a wrapper around a filesystem with benefits.

## What makes it special
* References:
  A reference is just a name in a text file marked with `[square brackets]`. This will signify to the application that there is an element somewhere else with that name. This can then be looked up and retrieved with a single command.

## What's coming
* Character creation
  Perhaps is biggest feature i am working on at the ability to create and manage player characters according to the D&D ruleset.

* Full tree customisation
  At the moment, the layout of Categories, Elements and articles is completely fixed, however I will soon be adding new commands to customise a more generalised tree shaped data pattern. Once this is implemented, the user will be able to group any number of items of the same type together into as many folders and subfolders as they desire.
  
* Filesystem virtualisation
  Currently I am working on a setting that will allow the folder hierarchy to be stored entirely within a configuration file. This will then be fully toggleable and serve the purpose of organisation versus storage optimisation.
  
## How to use it
* `hlp | help`
* `crt | create`
* `opn | open`
* `close`
* `add`
* `del`
* `slt | select`
* `vew | view`
* `lst | list`
* `edt | edit`
* `rnm | rename`
* `lkp | lookup`
* `cls | clear`
* `dir`