#include "line.hpp"

Line::Line(int startIndex,int endIndex,double theta,double yIntercept,const std::vector<float>& ranges){
  Line::startIndex = startIndex;
  Line::endIndex = endIndex;
  Line::theta = theta;
  Line::yIntercept = yIntercept;
  Line::ranges = ranges;
  
  startX = ranges[startIndex]*hokuyoCos(startIndex);
  startY = std::tan(theta)*startX + yIntercept;
  endX = ranges[endIndex]*hokuyoCos(endIndex);
  endY = std::tan(theta)*endX + yIntercept;
  
  dis = std::abs(yIntercept)/std::sqrt(1 + std::tan(theta)*std::tan(theta));
}

void Line::merge(Line line){
  /*lineは呼び出し元の次の線分でないといけない*/
  if(endIndex+1 != line.startIndex){
    std::cout << "LINE::merge() ERROR\n";
    return;
  }

  endIndex = line.endIndex;
  endX = line.endX;
  
  /*最小２乗法を用いてtheta,yInterceptを計算*/
  double xy=0,sumX=0,sumY=0,xSquared=0;
  for(int tmp=0;tmp<=endIndex;tmp++){
    xy += ranges[tmp]*ranges[tmp]*hokuyoCos(tmp)*hokuyoSin(tmp);
    sumX += ranges[tmp]*hokuyoCos(tmp);
    sumY += ranges[tmp]*hokuyoSin(tmp);
    xSquared += ranges[tmp]*ranges[tmp]*hokuyoCos(tmp)*hokuyoCos(tmp);
  }
  
  int n = endIndex - startIndex + 1;  
  theta = std::atan((n*xy - sumX*sumY)/(n*xSquared - sumX*sumX));
  yIntercept = (xSquared*sumY - xy*sumX)/(n*xSquared - sumX*sumX);

  startY = std::tan(theta)*ranges[startIndex] + yIntercept;
  endY = std::tan(theta)*ranges[endIndex] + yIntercept;

  dis = std::abs(yIntercept)/std::sqrt(1 + std::tan(theta)*std::tan(theta));
 
}


			    
