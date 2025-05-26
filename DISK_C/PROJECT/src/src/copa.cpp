#include "include.h"

int copy_file(char *source_path, char *dest_path) // 复制粘贴文件
{
  // printf("src_path:%s ?dest_path:%s\n", source_path, dest_path);
  FILE *source = fopen(source_path, "rb");
  if (source == NULL)
  {
    perror("unable to open src");
    return -1;
  }

  FILE *dest = fopen(dest_path, "wb");
  if (dest == NULL)
  {
    perror("unable to new");
    fclose(source);
    return -1;
  }

  char buffer[4096];
  size_t bytes_read;

  while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0)
  {
    if (fwrite(buffer, 1, bytes_read, dest) != bytes_read)
    {
      perror("fail to write");
      fclose(source);
      fclose(dest);
      return -1;
    }
  }

  if (ferror(source))
  {
    perror("fail to read src");
    fclose(source);
    fclose(dest);
    return -1;
  }

  fclose(source);
  fclose(dest);
  return 0;
}

// 复制粘贴文件（夹）
int c_p(char *source_path, char *dest_father_path) // 源文件绝对路径，目标所在文件夹绝对路径
{
  char dest_file_path[1024]; // 目标文件路径

  sprintf(dest_file_path, "%s\\%s", dest_father_path, path_to_name(source_path));

  if (get_file_type(source_path) != 2) // 如果是文件
  {
    copy_file(source_path, dest_file_path);
    return 1;
  }
  else // 如果是文件夹
  {
    DIR *dir;
    struct dirent *entry;

    // 创建目标文件夹
    if (mkdir(dest_file_path) != 0)
    {
      return -1;
    }

    dir = opendir(source_path);
    if (!dir)
    {
      perror("Failed to open directory");
      return -1; // 如果打开目录失败，停止读取
    }

    while ((entry = readdir(dir)) != NULL)
    {
      if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        continue;

      char *filename = entry->d_name; // 目标文件夹中的文件
      // char dest_son_path[128];
      char *dest_son_path; // 目标文件夹中的文件（夹）
      sprintf(dest_son_path, "%s\\%s", dest_father_path, path_to_name(source_path));
      c_p(get_file_path(source_path, filename), dest_son_path);
    }

    closedir(dir);
  }
  return 1;
}
// 删除文件
int rm_file(char *file_path)
{
  if (remove(file_path) == 0)
  {
    // printf("file %s del success\n", file_path);
    return 1;
  }
  else
  {
    perror("fail to del"); // 打印错误信息（如文件不存在、权限不足等）
    return 0;
  }
}
// 可删除文件或文件夹
int rm_dir(char *dir_path)
{
  char *file_path = dir_path;

  if (get_file_type(dir_path) != FOLD) // 如果是文件
  {
    // printf("removing %s\n", dir_path);
    remove(dir_path);
    return 1;
  }
  else // 如果是文件夹
  {
    struct dirent *entry;
    DIR *dir = opendir(dir_path);

    if (!dir)
    {
      perror("unable to open dir");
      return 0;
    }
    // 逐个删除文件夹里的文件

    while ((entry = readdir(dir)) != NULL)
    {
      if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      {
        continue;
      }
      char *new_path = get_file_path(file_path, (entry->d_name));
      unsigned char type = get_file_type(new_path);
      if (type == FOLD)
      {
        rm_dir(new_path);
      }
      else
      {
        rm_file(new_path);
      }
      free(new_path);
    }
    closedir(dir);
    // 删除空目录
    rmdir(dir_path);
  }
  return 1;
}
