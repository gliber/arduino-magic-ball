public class GameIcon
{
  int posX;
    int posY;
    int sizeX,sizeY;
    PImage img;
    public int value;
  public GameIcon(String file_name, int row, int column, int v)
  {
    value = v;
     posX = width/4 * column;
     posY = height/4 * row;
      img = loadImage(file_name);
     sizeX = min(width,height)/4;
     sizeY = sizeX;
    
     
  }
  
  public void draw()
  {    
     imageMode(CENTER);
  
    stroke(0);
    strokeWeight(4);
    fill(50);
    rect(posX+15,posY+15,sizeX,sizeY,30);
    fill(255);
    rect(posX,posY,sizeX,sizeY,20);
    image(img,posX,posY,sizeX,sizeY);
  }
  
  public boolean pressed()
  {
    return (mouseX>posX && mouseX < posX+sizeX &&
    mouseY>posY && mouseY < posY+sizeY);
  }

}