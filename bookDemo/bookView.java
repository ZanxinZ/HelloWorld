package bookDemo;

import java.util.Scanner;

/**
 * 图书管理的界面
 * @author pi
 *
 */
public class bookView {
	private Scanner input=null;
	private BookBiz bookBiz;
	
	
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
		}else{
			System.out.println("程序退出，谢谢使用！");
		}
	}
	
	
	
	private void showMainView() {
		while(true){
		System.out.println("X10图书管理系统>>主菜单");
		System.out.println("1、新增图书\t2、删除图书\t3、查看所有图书\t4、按编号查询\t5、入库\t6、出库");
		System.out.print("请选择");
	
		int a=1;
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
				showBook();
				i=0;
				break;
			case 4:
				findBook();
				i=0;
				break;
			case 5:
				bookIn();
				i=0;
				break;
			case 6:
				bookOut();
				i=0;
				break;
				default:
					System.out.println("输入错误，请重新输入");
					i=1;
					break;
			}
		}
		if(a==3){
			break;
		}
		}
		System.out.println("程序退出，谢谢使用！");
	}
	/**
	 * 增加新书
	 */
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
			showBook();
		}
		/**
		 * 删除书
		 */
		private void deleteBookView(){
			System.out.println("X10图书管理系统>>主菜单>>删除图书");
			System.out.print("输入图书编号：");
			Book delBook=new Book();
			delBook=bookBiz.findBookByNum(input.next());
			if(delBook==null){
				System.out.println("未找到图书");
			}
			if(bookBiz.deleteBook(delBook)){
				System.out.println("删除成功");
				showBook();
			}else {
				System.out.println("删除失败");
			}
		
		}
		/**
		 * 查找图书
		 */
		private void findBook(){
			System.out.println("X10图书管理系统>>主菜单>>查找图书");
			System.out.print("输入图书编号：");
			Book seekBook = new Book();
			seekBook.setNum(input.next());
			seekBook =	bookBiz.findBookByNum(seekBook.getNum());
			if(!(seekBook==null)){
				System.out.println("已找到：");
				showBook(seekBook);
			}else {
				System.out.println("未找到图书，请正确输入图书编号");
			}
		}
		/**
		 * 书籍入库
		 */
		private void bookIn(){
			System.out.println("X10图书管理系统>>主菜单>>入库");
			System.out.print("输入图书编号：");
			String num=input.next();
			Book tempBook=new Book();
			tempBook=bookBiz.findBookByNum(num);
			if(tempBook==null){
				System.out.println("书籍没有找到");
			}else{
				System.out.println("入库的数量：");
				int count=input.nextInt();
				bookBiz.bookIn(tempBook.getNum(), count);
				System.out.println("入库成功");
				showBook(tempBook);
			}
		}
		private void bookOut(){
			System.out.println("X10图书管理系统>>主菜单>>出库");
			System.out.print("输入图书编号：");
			String num=input.next();
			Book tempBook=new Book();
			tempBook=bookBiz.findBookByNum(num);
			if(tempBook==null){
				System.out.println("书籍没有找到");
			}else{
				System.out.println("出库的数量：");
				int count=input.nextInt();
				if(tempBook.getCount()<count){
					System.out.println("库存不足");
				}
				if(bookBiz.bookOut(tempBook.getNum(), count)){
					System.out.println("出库成功");					
				}else{
					System.out.println("出库失败");
				}
				showBook(tempBook);
			}
			
		}
		/**
		 * 显示一本图书
		 * @return 是否显示成功
		 */
		public boolean showBook(Book book){
			System.out.println("ID\t书名\t\t\t\t编号\t\t\t序列号\t\t\t库存");		
			System.out.println(book.getId()+"\t"+book.getName()+
					"\t\t\t"+book.getNum()+"\t\t"+book.getSeriesNum()+
					"\t\t\t"+book.getCount());
			return true;
		}
		/**
		 * 显示所有图书
		 * @return 是否显示成功
		 */
		public boolean showBook(){
			int count=bookBiz.findStoreCount();
			if(count==0){
				System.out.println("现在仓库空空，啥也没有");
			}else{
				System.out.println("ID\t书名\t\t\t\t编号\t\t\t序列号\t\t\t库存");				
			}
			for (int i = 0; i < count; i++) {
				System.out.println(bookBiz.getInstanceBook(i).getId()+"\t"+bookBiz.getInstanceBook(i).getName()+
						"\t\t\t"+bookBiz.getInstanceBook(i).getNum()+"\t\t"+bookBiz.getInstanceBook(i).getSeriesNum()+
						"\t\t\t"+bookBiz.getInstanceBook(i).getCount());
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
