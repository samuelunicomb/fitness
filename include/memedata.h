#ifndef MEMEDATA_H_
#define MEMEDATA_H_

struct memedata{
  unsigned int popularity;  // number of retweets
  unsigned int abundance;   // number of screens the meme is on
  double birthtime;         // time of birth
  double wp, wr, wb;        // fitness type; post, repost, breadth

  memedata(){};

  memedata(unsigned int p, unsigned int a, double b, double c, double d, double e)
    : popularity(p), abundance(a), birthtime(b), wp(c), wr(d), wb(e) {}
};

#endif
