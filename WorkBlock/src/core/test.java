package core;
/**
 * 测试类
 * 
 * @author pi
 *记录
 *可以模仿event，造一个抽象类，供事件、地点、时间、人物 继承
 */
public class test {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("Welcome to WorkBlock");
	//Board board=new Board(2);
		Event event1=new Event();
		for (int i = 0; i < event1.getThings().length; i++) {
			System.out.print(event1.getThings()[i].getTaskName()+":\t");
			for (int j = 0; j < event1.getThings()[i].getObjects().length; j++) {
				System.out.print(event1.getThings()[i].getObjects()[j].getObject()+"\t");
				
			}
			System.out.println();
		}
		
	}

}
