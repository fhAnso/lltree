# lltree - Enhanced Tree Listing

The lltree command is a fusion of the tree and ll alias (ls -la)
command and is designed to provide an extended view of the file 
structure. This project aims to augment the tree 
command by incorporating additional details such as file 
permissions, user, and creation date. 

## Setup:
- `Clone` the repository:
```
git clone https://github.com/fhAnso/lltree.git
```

- Use the `make` command to `compile` and `install` the lltree project:
```
make && make install
``` 

## Usage:
- The `syntax` is as follows:
```
lltree <path> # `<path>`: target directory (Can be either an absolute or relative path)
```

- To `uninstall` lltree use:
```
make uninstall
```

## License
The lltree project is published under the [BSD 3-Clause License](https://github.com/fhAnso/lltree/blob/main/LICENSE) license.
