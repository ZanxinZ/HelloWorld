package bookDemo;

import java.util.Scanner;

/**
 * 图书管理的界面
 * @author pi
 *
 */
public class bookView {
	private Scanner input=null;;
	private BookBiz bookBiz=null;
	
	
	public bookView() {
		super();
		input=new Scanner(System.in);
		bookBiz=new BookBiz();
		System.out.println("******************************");
		System.out.println("\t欢迎使用X10图书管理系统");
		System.out.println("\t1、登录\t2、退出系统");
		System.out.println("******************************");
		System.out.print("请选择：");
		String choice=input.next();
		if("1".equals(choice)){
			System.out.println("登录功能未上线，默认已登录");
			showMainView();
		}
	}
	
	
	
	private void showMainView() {
		System.out.println("X10图书管理系统>>主菜单");
		System.out.println("1、新增图书\t2、删除图书\t3、查看所有图书\t4、按编号查询\t5、入库\t6、出库");
		System.out.print("请选择");
		
		for(int i=1;i==1;)
		{
			int choice=new Integer(input.next()).intValue();
			switch(choice){
			case 1:
				addNewBookView();
				i=0;
				break;
			case 2:
				deleteBookView();
				i=0;
				break;
			case 3:
				showBooks(0, null);
				i=0;
				break;
			case 4:
				i=0;
				break;
			case 5:
				i=0;
				break;
			case 6:
				i=0;
				break;
				default:
					System.out.println("输入错误，请重新输入");
					i=1;
					break;
			}
		}
	}
		private void addNewBookView(){
			System.out.println("X10图书管理系统>>主菜单>>新增图书");//缓冲区域有问题，i你普通需要修改
			Book book=new Book(null, null,0);
			System.out.print("内部编号：");
			book.setNum(input.next());
			System.out.println("书名：");
			book.setName(input.next());
			System.out.println("序列号：");
			book.setSeriesNum(input.next());
			System.out.println("书本数量：");
			book.setCount(input.nextInt());
			bookBiz.addBook(book);
			showBooks(0 ,null);
		}
		private void deleteBookView(){
			System.out.println("X10图书管理系统>>主菜单>>删除图书");
			System.out.print("输入图书编号：");
			if(bookBiz.deleteBook(bookBiz.finddBookByNum(input.next()))){
				System.out.println("删除成功");
			}else {
				System.out.println("删除失败");
			}
		
		}
		/**
		 * 显示图书
		 * @param count 显示的数量
		 * @return 是否显示成功
		 */
		public boolean showBooks(int num,Book book){
			int count=bookBiz.findStoreCount();
			if(num==0){
				System.out.println("ID\t书名\t\t\t\t编号\t\t\t序列号\t\t\t库存");
				for (int i = 0; i < count; i++) {
					System.out.println(bookBiz.getInstanceBook(i).getId()+"\t"+bookBiz.getInstanceBook(i).getName()+
							"\t\t\t"+bookBiz.getInstanceBook(i).getNum()+"\t\t"+bookBiz.getInstanceBook(i).getSeriesNum()+
							"\t\t\t"+bookBiz.getInstanceBook(i).getCount());
				}
			}
			else {
				System.out.println("不是0");
			}
			return true;
		}

	public BookBiz getBookBiz() {
		return bookBiz;
	}
	public void setBookBiz(BookBiz bookBiz) {
		this.bookBiz = bookBiz;
	}
	
}
