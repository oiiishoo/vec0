//4.9.2024 @ 3:27
struct vec0 {
	
	//size_t len;
	size_t sz;
	void* ptr;
	//Shouldn't be used by user if they already had initialized the object
	vec0() {
		if (ptr)delete ptr;
		sz = 0;
		ptr = 0;
	}
	//Prealloc some size of chars
	vec0(size_t size) {
		if (ptr)realloc(sz+size,0);
		else ptr = new char[size];
	}
	//Constructor with automated adding of array
	template<typename T>
	vec0(T a) {
		if (ptr)delete ptr;
		size_t t=strlen((char*)a);
		sz = t;
		ptr=new char[t];
		for (size_t i = 0; i < t; i++)
		{
			((char*)ptr)[i] = ((char*)a)[i];
		}
		((char*)ptr)[t] = 0;
	}
	//Add element to the end
	void append(char a) {
		realloc(sz+1,0);
		((char*)ptr)[sz-1] = a;
	}
	template<typename T>
	void strappend(T*a) {
		if (sizeof(a)==sizeof(void*)) {
			size_t t = strlen(a);
			size_t d = sz + t;
			realloc(sz + t, 0);
			for (size_t i = sz - t, l = 0; i < d; i++)
			{
				((char*)ptr)[i] = a[l];
				l++;
			}
		}
	}
	//Intended to be used by object but open for everyone
	void realloc(size_t siz,size_t par) {
		if (!ptr)return;
		if (par) {
			char* t = new char[siz+par+1];
			for (size_t i = 0; i < siz; i++)
			{
				t[i+par] = ((char*)ptr)[i];
			}
			siz += par;
			delete ptr;
			ptr = (void*)t;
			t[siz] = 0;
			sz = siz;
		}
		else {
			char* t = new char[siz + 1];
			for (size_t i = 0; i < sz; i++)
			{
				t[i] = ((char*)ptr)[i];
			}
			delete ptr;
			ptr = (void*)t;
			t[siz] = 0;
			sz = siz;
		}
	}
	//Put an a char or char array in first order
	template<typename T>
	void pushback(T a) {
		if (sizeof(a) == 1) {
			realloc(sz+1,1);
			((char*)ptr)[0] = (char)a;
		}
		else {
			size_t tm = strlen(a);
			size_t t = sz + tm;
			realloc(sz, tm);
			for (size_t i = 0; i < tm; i++)
			{
				//printf("%d %d\n", i, t);
				((char*)ptr)[i] = ((char*)a)[i];
			}
		}
	}
	//Intended to revert elements order
	void revert() {
		if (!sz)return;
		char* t = new char[sz+1];
		if (!t)return;
		size_t tm=0;
		for (size_t i = sz; i > 0; i--)
		{
			((char*)t)[tm]=((char*)ptr)[i-1];
			tm++;
		}
		delete ptr;
		ptr = t;
		t[sz] = 0;
	}
//There are in a plan of making the xorstr array of values, so stronger symmetric encryption is can be made
	template<typename T>
	void xorstr (T a) {
		char t=sz % sizeof(a);
		size_t tm=sz+t;
		char* b = new char[tm+1];
		
		size_t i=0;
		while(i<(tm?1:tm/8)){
			((size_t*)b)[i] = ((size_t*)ptr)[i] ^ a;
			
			i++;
		}
		b[i?i*8:0] = 0;
		delete ptr;
		ptr = b;
		sz = i?i*8:0;
	}
	//Looks like destructor?
	~vec0() {
		if(ptr)delete ptr;
	}
};

int main()
{
	vec0 d("xorlayer");
	d.xorstr(0x198653469dffffff);
	for (size_t i = 0; i < d.sz; i++)
	{
		printf("%x ", ((char*)d.ptr)[i] & 0xff);
	}
	printf("\n");
	d.xorstr(0xf865415f12122f1a);
	for (size_t i = 0; i < d.sz; i++)
	{
		printf("%x ", ((char*)d.ptr)[i] & 0xff);
	}
	printf("\n");
	d.xorstr(0xf865415f12122f1a);
	for (size_t i = 0; i < d.sz; i++)
	{
		printf("%x ", ((char*)d.ptr)[i] & 0xff);
	}
	printf("\n");
	d.xorstr(0x198653469dffffff);
	for (size_t i = 0; i < d.sz; i++)
	{
		printf("%02x ", ((char*)d.ptr)[i] & 0xff);
	}
}
