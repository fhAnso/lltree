/**
* lltree - Enhanced Tree Listing, v1.0.5
* 
* The lltree command is a fusion of the tree and ll alias (ls -la)
* command and is designed to provide an extended view of the file 
* structure. This project aims to augment the tree 
* command by incorporating additional details such as file 
* permissions, user, and creation date. 
*  
* Author: fhAnso
* License: BSD 3-Clause License
* GitHub Repository: https://github.com/fhAnso/lltree
*/

#ifndef UTILS_H
#define UTILS_H

#include "externs.h"
#include "lltree.h"

int is_owner(char *owner);
char *owner(char *filename);
char *mod_date(char *filename);
char *get_permissions(char *filename);

#endif
