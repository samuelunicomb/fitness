#ifndef MEMEDATA_H_
#define MEMEDATA_H_

struct memedata{
  unsigned int popularity;  // number of retweets
  unsigned int abundance;   // number of screens the meme is on
  double birthtime;         // time of birth
  double wp, wr, wb;        // fitness type; post, repost, breadth

  // TODO not sure how long this will be here
  //unsigned int progeny;

  memedata(){};

  memedata(unsigned int p, unsigned int a, double b, double c, double d, double e)
    : popularity(p), abundance(a), birthtime(b), wp(c), wr(d), wb(e) {}
};


struct memedatasorted{
  memedatasorted(int a, int b, double c) : id(a), abundance(b), wr(c) {}

  int id, abundance;
  double wr;

  bool operator<(const memedatasorted& rhs) const{
    if(abundance != rhs.abundance) 
      return abundance < rhs.abundance;
    else
      return id < rhs.id;
  }
};

#endif
