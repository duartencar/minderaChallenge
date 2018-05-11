#ifndef LINEGROUP_H_
#define LINEGROUP_H_

class LineGroup {
private:
   int leftX;
   int width;
   int y;
public:
   LineGroup(int x, int y);
   void setWidth(int w);
   void print();
   int  getLineNumber();
   int  getRightX();
   int  getLeftX();
   bool nextTo(LineGroup * lg);
   bool isSingle();
};

#endif /* LINEGROUP_H_ */
