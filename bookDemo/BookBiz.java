package bookDemo;
/**
 * 图书业务类
 * 存储图书
 * @author pi
 *
 */
public class BookBiz {
		private Book[] bookStore=new Book[20];
		private int storeCount;//书的存储量,从0开始
		//查看图书
		//增加图书
		//删除图书
		//退出
		
		/**
		 * 查看目前图书
		 * @return 返回图书
		 */
		Book[] getInstanceBook(){
		
			return bookStore;
		}
		/**
		 * 添加书籍
		 * @param book
		 * @return 添加是否成功
		 */
		boolean addBook(Book book){
			//书库已满，存储失败
			if(storeCount>=bookStore.length){
				return false;
			}
			else{
				for (int i = 0; i < bookStore.length; i++) {
					if(bookStore[i]==null){
						//书的数组有位置，存书
						bookStore[i]=book;
						storeCount++;//储量+1
						break;
					}
				}
			}
			return true;
			
		}
		/**
		 * 删除书籍
		 * @param book 
		 * @return  删除是否成功
		 */
		boolean deleteBook(Book book){
			int searchIndex=-1;//寻找书籍的下标
			//图书数量为0,删除失败
			if(storeCount==0){
				return false;
			}
			else {
				for (int i = 0; i < bookStore.length; i++) {
					if(book.getSeriesNum().equals(bookStore[i].getSeriesNum())){
						//找到对应的书籍，进行删除操作
						searchIndex=i;
						
					}
				}
			}
			return true;
		}
		/**
		 * 书籍入库
		 * @param num 入库数量
		 * @return 是否入库成功
		 */
		boolean bookIn(String series,int num){
			Book bookTemp=findBookBySeries(series);
			if(bookTemp==null){//书籍找不到
				return false;//入库失败
			}
			bookTemp.setCount(bookTemp.getCount()+num);
			return true;//入库成功
		}
		/**
		 * 书籍出库
		 * @param num 出库数量
		 * @return 
		 */
		boolean bookOut(String series,int num){
			Book bookTemp=findBookBySeries(series);
			if(bookTemp==null||num>bookTemp.getCount()){//书籍找不到
				return false;//出库失败
			}
			bookTemp.setCount(bookTemp.getCount()-num);
			return true;//出库成功
		}
		/**
		 * 计算书库里有几本书
		 * @return
		 */
		int findStoreCount(){
			int count=0;
			for (int i = 0; i < bookStore.length; i++) {
				if(!(bookStore[i]==null)){
					count++;
				}
			}
			return count;
		}
		/**
		 * 通过序列号查找书籍
		 * @param series 序列号
		 * @return 若找到，返回找到的书。若没有找到，返回空
		 */
		Book findBookBySeries(String series){
			for (int i = 0; i < bookStore.length; i++) {
				if(bookStore[i].getSeriesNum().equals(series)){
					//找到了
					return bookStore[i];
				}
			}
			return null;
		}
}
