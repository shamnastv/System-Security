#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<inttypes.h>
#define MAX_SIZE 3000
typedef uint32_t uint32;
typedef uint8_t uint8;
typedef int8_t int8;
static const char _base64[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int pg_b64_encode(const char *src, int len, char *dst)
{
	char	   *p;
	const char *s,*end = src + len;
	int	pos = 2;
	uint32	buf = 0;

	s = src;
	p = dst;

	while (s < end)
	{
		buf |= (unsigned char) *s << (pos << 3);
		pos--;
		s++;

		/* write it out */
		if (pos < 0)
		{
			*p++ = _base64[(buf >> 18) & 0x3f];
			*p++ = _base64[(buf >> 12) & 0x3f];
			*p++ = _base64[(buf >> 6) & 0x3f];
			*p++ = _base64[buf & 0x3f];

			pos = 2;
			buf = 0;
		}
	}
	if (pos != 2)
	{
		*p++ = _base64[(buf >> 18) & 0x3f];
		*p++ = _base64[(buf >> 12) & 0x3f];
		*p++ = (pos == 0) ? _base64[(buf >> 6) & 0x3f] : '=';
		*p++ = '=';
	}

	return p - dst;
}

void call_encode()
{
  char dest[MAX_SIZE];
  char source[MAX_SIZE];
  FILE *f;
  f=fopen("input.txt","r");
  if (f==NULL){
        printf("file doesnt exist?!");
	return;
    }

    int i=0;
    while (fscanf(f,"%x",&source[i]) != EOF){
        i++;
    }

  pg_b64_encode(source, i, dest);
  printf("%s\n",dest);

}


void main()
{
  call_encode();
}
