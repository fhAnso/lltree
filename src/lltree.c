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

#include "headers/lltree.h"

void dirwalk(counter_t *counter, char *path, char *prefix) 
{
	DIR *dir = opendir(path);
	
	if (!dir) 
	{
		fprintf(stderr, "opendir: %s\n", strerror(errno));
		exit(-1);
	}

	struct dirent *dir_ptr;
	struct dirent **child_dir;

	// Scan for dir entries 
	int sc = scandir(path, &child_dir, NULL, alphasort);
	
	if (sc < 0) 
	{
		fprintf(stderr, "scandir: %s\n", strerror(errno));
		exit(-1);
	}

	counter->dir_count++;

	for (int iter = 0; iter < sc; iter++) 
	{
		dir_ptr = child_dir[iter];
		char *ca = "│   ", *cb = "├── ";

		if (iter == (sc - 1)) 
		{
			cb = "└── ";
			ca = "    ";
		}

		char *entry = dir_ptr->d_name;

		// Remove last char from current entry if last char is '/'
		if (path[strlen(path) - 1] == '/') 
		{
			path[strlen(path) - 1] = '\0';
		}

		char child_path[PATH_MAX]; // Current child path
		snprintf(child_path, sizeof(child_path), "%s/%s", path, entry);

		char new_prefix[PATH_MAX]; // Output
		snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, ca);

		struct stat link_stat;

		// Identify symbolic links
		if (lstat(child_path, &link_stat) == 0 && S_ISLNK(link_stat.st_mode)) 
		{
			char symlink_dest[PATH_MAX];
			// Follow symbolic link
			ssize_t len = readlink(child_path, symlink_dest, sizeof(symlink_dest) - 1);
			
			if (len != -1) 
			{
				symlink_dest[len] = '\0'; 
				printf("%s%s [symlink] %s -> %s\n", prefix, cb, child_path, symlink_dest);
			}

			continue; 
		}
		
		char *permission = get_permissions(child_path);
		char *modify_date = mod_date(child_path);
		char *file_owner = owner(child_path);

		char format_owner[50];
		int io = is_owner(file_owner);
		
		if (io == -1) 
		{
			sprintf(format_owner, "ERROR RESOLVING OWNER");
		}
		else 
		{
			sprintf(format_owner, "%s", file_owner);
		}
		
		// Skip dot entries
		int eval = strcmp(entry, ".") != 0 && strcmp(entry, "..");
		
		if (eval != 0) 
		{
			if (dir_ptr->d_type == DT_DIR) 
			{
				// Directory: append '/'
				printf("%s%s%s  %s  %s  %s/\n", 
					prefix, cb, permission, format_owner, modify_date, entry);
			}
			else
			{
				// File
				printf("%s%s%s  %s  %s  %s\n", 
					prefix, cb, permission, format_owner, modify_date, entry);
			}
		} 

		free(modify_date);
		free(permission);

		if (dir_ptr->d_type == DT_DIR && eval) 
		{
			dirwalk(counter, child_path, new_prefix);
		} 
		else 
		{
			counter->file_count++;
		}

		free(dir_ptr);
	}

	closedir(dir);
	free(child_dir);
}

int main(int argc, char **argv) 
{
	char *dir;
	argc > 1 ? (dir = argv[1]) : (dir = ".");

	counter_t counter = {0, 0};
	clock_t start = clock();

	printf("lltree, v1.0.5\n");
	printf(" --- Permissions - Owner - Last Modified - File\n");
	printf("%s\n", dir);
	dirwalk(&counter, dir, "");

	clock_t end = clock();
	double elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;

	printf("\n%d directories, %d files, time needed: %fs\n", 
			counter.dir_count - 1, counter.file_count, elapsed);

	return 0;
}
