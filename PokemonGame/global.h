#define BUF_SIZE 26496			// about 10 seconds of buffer (@ 48K samples/sec)
#define bg_BUF_SIZE 524288			//각각의 소리들의 데이터가 다르므로
#define dead_BUF_SIZE 283392		//버퍼의 사이즈를 DEFINE 한다.
#define gung_BUF_SIZE 108288
#define BUF_THRESHOLD 96		// 75% of 128 word buffer
