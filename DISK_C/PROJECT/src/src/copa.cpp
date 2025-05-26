#include "include.h"

int copy_file(char *source_path, char *dest_path) // ����ճ���ļ�
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

// ����ճ���ļ����У�
int c_p(char *source_path, char *dest_father_path) // Դ�ļ�����·����Ŀ�������ļ��о���·��
{
  char dest_file_path[1024]; // Ŀ���ļ�·��

  sprintf(dest_file_path, "%s\\%s", dest_father_path, path_to_name(source_path));

  if (get_file_type(source_path) != 2) // ������ļ�
  {
    copy_file(source_path, dest_file_path);
    return 1;
  }
  else // ������ļ���
  {
    DIR *dir;
    struct dirent *entry;

    // ����Ŀ���ļ���
    if (mkdir(dest_file_path) != 0)
    {
      return -1;
    }

    dir = opendir(source_path);
    if (!dir)
    {
      perror("Failed to open directory");
      return -1; // �����Ŀ¼ʧ�ܣ�ֹͣ��ȡ
    }

    while ((entry = readdir(dir)) != NULL)
    {
      if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        continue;

      char *filename = entry->d_name; // Ŀ���ļ����е��ļ�
      // char dest_son_path[128];
      char *dest_son_path; // Ŀ���ļ����е��ļ����У�
      sprintf(dest_son_path, "%s\\%s", dest_father_path, path_to_name(source_path));
      c_p(get_file_path(source_path, filename), dest_son_path);
    }

    closedir(dir);
  }
  return 1;
}
// ɾ���ļ�
int rm_file(char *file_path)
{
  if (remove(file_path) == 0)
  {
    // printf("file %s del success\n", file_path);
    return 1;
  }
  else
  {
    perror("fail to del"); // ��ӡ������Ϣ�����ļ������ڡ�Ȩ�޲���ȣ�
    return 0;
  }
}
// ��ɾ���ļ����ļ���
int rm_dir(char *dir_path)
{
  char *file_path = dir_path;

  if (get_file_type(dir_path) != FOLD) // ������ļ�
  {
    // printf("removing %s\n", dir_path);
    remove(dir_path);
    return 1;
  }
  else // ������ļ���
  {
    struct dirent *entry;
    DIR *dir = opendir(dir_path);

    if (!dir)
    {
      perror("unable to open dir");
      return 0;
    }
    // ���ɾ���ļ�������ļ�

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
    // ɾ����Ŀ¼
    rmdir(dir_path);
  }
  return 1;
}
