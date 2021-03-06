#include "pa02.h"

/**
 * Count the number of characters in a null-terminated string 's' 
 * (not counting the null character).
 *
 * Example: my_strlen("foo") should yield 3.
 */
int my_strlen(const char * s)
{
  int ind = 0; //Array index value
  int len = 0; //Length of the array

  while(s[ind] != '\0')
  {
    len++;
    ind++;
  }

  return len;
}

/**
 * Count the number of occurrences of a particular character 'c' in a
 * null-terminated string 's'.
 *
 * Example: my_countchar("foo", 'o') should yield 2.
 */
int my_countchar(const char * s, char c)
{
  int ind = 0; //Array index value
  int count = 0; //Number of occurences of the character

  while(s[ind] != '\0')
  {
    if(s[ind] == c)
    {
      count++;
    }
    ind++;
  }

  return count;
}

/**
 * Convert an entire null-terminated string 's' to uppercase.  Only
 * alphabetical characters should be converted; numbers and symbols
 * should not be affected.  Hint: toupper(c) is a macro that yields
 * the uppercase version of a character c.
 *
 * Example: char foobar[10] = "foobar";
 * my_strupper(foobar) yields "FOOBAR".
 */
void my_strupper(char * s)
{
  int ind = 0; //Array index value

  while(s[ind] != '\0')
  {
    if(s[ind] < 123 && s[ind] > 96)
    {
      s[ind] -= 32; //ASCII difference between capital and lowercase letters
    }
    ind++;
  }
}

/**
 * Convert an entire null-terminated string 's' to lowercase.  Only
 * alphabetical characters should be converted; numbers and symbols
 * should not be affected.  Hint: tolower(c) is a macro that yields
 * the lowercase version of a character 'c'.
 *
 * Example: char foobar[10] = "FOOBAR";
 * my_strupper(foobar) yields "foobar".
 */
void my_strlower(char * s)
{
  int ind = 0; //Array index value

  while(s[ind] != '\0')
  {
    if(s[ind] < 91 && s[ind] > 64)
    {
      s[ind] += 32; //ASCII difference between capital and lowercase letters
    }
    ind++;
  }
}

/**
 * Copy the contents of a null-terminated string 's2' into the memory
 * pointed to by 's1'.  Any existing data in 's1' will be overwritten by
 * the contents of 's2'.  Note: you can assume that there is sufficient
 * memory available in 's1'.  Hint: Don't forget to terminate the new
 * string with '\0'!
 * 
 * Example: char foo[10];
 * my_strcpy(foo, "foo") yields "foo".
 */
void my_strcpy(char * s1, const char * s2)
{
  int ind = 0; //Array index value

  do
  {
    s1[ind] = s2[ind];
    ind++;
  }while(s1[ind] != '\0' || s2[ind] != '\0');
}

/**
 * Copy the first 'n' characters of a null-terminated string 's2' into the
 * memory pointed to by 's1'. Any existing data in 's1' will be
 * overwritten by the contents of 's2'.  Note: you can assume that there
 * is sufficient memory available in 's1'.  Hint: Don't forget to
 * terminate the new string with '\0'!
 * 
 * Example: char foo[10];
 * my_strncpy(foo, "foo", 1) yields "f".
 */
void my_strncpy(char * s1, const char * s2, int num)
{
  int ind = 0; //Array index value

  do 
  {
    if(ind < num)
    {
      s1[ind] = s2[ind];
    }
    else
    {
      s1[ind] = 0;
    }

    ind++;
  }while(s1[ind] != '\0' || s2[ind] != '\0');
}


/** 
 * Concatenate (append) the contents of a null-terminated string 's2'
 * onto the end of the null-terminated string 's1'.  Note: you can
 * assume that there is sufficient memory available in 's1'.  Hint:
 * Don't forget to terminate the new string with '\0'!
 * 
 * Example: char foo[10] = "foo";
 * my_strcat(foo, "bar") yields "foobar".
 */
void my_strcat(char * s1, const char * s2) 
{
  int ind = 0; //Array index value
  int len = 0; //Array length

  while(s1[len++] != '\0');

  while(s2[ind] != '\0')
  {
    s1[len - 1] = s2[ind++];
    len++;
  }
}

/** 
 * Concatenate (append) the first n characters of a null-terminated
 * string 's2' onto the end of the null-terminated string 's1'.  Note: you
 * can assume that there is sufficient memory available in 's1'.  Hint:
 * Don't forget to terminate the new string with '\0'!
 * 
 * Example: char foo[10] = "foo";
 * my_strcat(foo, "bar", 1) yields "foob".
 */
void my_strncat(char * s1, const char * s2, int num)
{
  int ind = 0; //Array index value
  int len = 0; //Array length

  while(s1[len++] != '\0');

  do
  {
    if(ind < num)
    {
      s1[len - 1] = s2[ind++];
    }
    else
    {
      s1[len - 1] = 0;
    }
    len++;
    ind++;
  }while(ind < num || s1[ind] != '\0' || s2[ind] != '\0');
}

/**
 * Return a pointer to the first occurrence of a null-terminated
 * substring 's2' in a null-terminated string 's1'.  If 's2' does not appear
 * in 's1', the empty (NULL) pointer is returned.
 * 
 * Example: my_strstr("hello world!", "test") will yield 0 (NULL).
 * Example(2): my_strstr("foobar", "bar") will yield a pointer to the
 * "bar" portion of the "foobar" argument.
 */

const char *my_strstr(const char * s1, const char * s2)
{
  int length; //Length of s1
  int length2; //Length of s2
  int ind = 0; //Index value
  int add = 0; //Index offset value

  const char *address;
  address = NULL;

  length = my_strlen(s1);
  length2 = my_strlen(s2);

  while(length > 0)
  {
    if(s1[ind] == s2[0])
    {
      add = 0;

      while(s1[ind + add] == s2[add] && length != 0)
      {
        add++;
        length--;
      }
      if(length == 0 && length2 == add)
      {
        address = &s1[ind];
        length = 1;
      }
      else
      {
        ind += add;
      }
    }
    length--;
    ind++;
  }

  return address;
}


/**
 * Insert a null-terminated string s2 in the null-terminated string s1
 * at position pos.  All characters following position pos in s1 will
 * be moved to follow directly after the inserted characters from s2;
 * no characters will be overwritten.  Note: you can assume that there
 * is sufficient memory available in s1.
 * 
 * Hint: there is no need to create any temporary memory; simply copy
 * the contents of the string after position pos to its new location
 * starting from the back of the string and going forwards.
 * 
 * Insertions should happen BEFORE the character position referenced
 * by pos.  In other words, inserting s2 at position 0 (the first
 * character of a string) in s1 is equivalent to the string s2
 * followed by string s1.
 * 
 * If the character position pos is higher (or equivalent to) the
 * length of string s1, s2 will simply be appended to the end of s1
 * (i.e. it is equivalent to my_strcat(s1, s2);
 * 
 * Example: char foo[10] = "foo";
 * my_strinsert(foo, "bar", 0) yields "barfoo".
 * 
 * Example(2): char foo[10] = "foo";
 * my_strinsert(foo, "bar", 100) yields "foobar".
 */
void my_strinsert(char *s1, const char *s2, int pos)
{
  int len1 = my_strlen(s1); //Length of string 1
  int len2 = my_strlen(s2); //Length of string 2
  int ind; //Array index value

  if(pos > len1)
  {
    pos = len1; //Check to make sure position isn't outside of the array
  }

  for(ind = (len1 + len2); ind >= (pos + len2); ind--)
  {
    s1[ind] = s1[ind - len2];
  }

  for(ind = pos; ind < pos + len2; ind++)
  {
    s1[ind] = s2[ind - pos];
  }

  //No need for null character, it was already taken care of in the copying
}

/**
 * Delete a portion of the null-terminated string s that starts at
 * character position pos and is length characters long.  All
 * characters following position pos + length in s will be moved up to
 * follow directly after the characters before position pos. 
 * 
 * Hint: there is no need to create any temporary memory; simply copy
 * the contents of the string after position pos + length to their new
 * location.
 * 
 * Deletions should happen BEFORE the character position referenced by
 * pos.  In other words, deleting position 0 (the first character of a
 * string) in s means will start deleting from the first character.
 *
 * If the character position pos is higher (or equivalent to) the
 * length of string s, the function will do nothing.
 * 
 * If the length of the deleted portion from its starting position pos
 * extends past the end of the string, the remainder of the string
 * will be deleted.
 * 
 * Example: char foo[10] = "foobar";
 * my_strdelete(foo, 3, 3) yields "foo".
 *
 * Example(2): char foo[10] = "foobar";
 * my_strdelete(foo, 0, 3) yields "bar".
 * 
 * Example(3): char foo[10] = "foobar";
 * my_strdelete(foo, 0, 34) yields "".
 */
void my_strdelete(char *s, int pos, int length)
{
  int len = my_strlen(s); //Length of the given string
  int ind; //Array index vlue

  if(pos > len)
  {
  }
  else
  {
    if(length > len - pos)
    {
      length = len - pos; //Make sure values aren't out of given range
    }

    for(ind = pos; ind < len - length + pos; ind++)
    {
      s[ind] = s[length + ind];
    }

    s[len - length] = '\0'; //Append null character to end string
  }
}
