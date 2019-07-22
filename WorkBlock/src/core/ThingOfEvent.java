package core;
/**
 * 任务
 * 包含任务对象
 * @author pi
 *
 */
public class ThingOfEvent {
	private String taskName=null;
	private objectOfThing []objects=new objectOfThing [10];//具体对象数组
	
	public ThingOfEvent() {
		// TODO Auto-generated constructor stub
		for(int i=0;i<objects.length;i++){
			objects[i]=new objectOfThing();
			objects[i].setObject("默认对象"+(i+1));
		}
	}
	public objectOfThing[] getObjects() {
		return objects;
	}

	public void setObjects(objectOfThing[] objects) {
		this.objects = objects;
	}
	public String getTaskName() {
		return taskName;
	}
	public void setTaskName(String taskName) {
		this.taskName = taskName;
	}
	
	
}
