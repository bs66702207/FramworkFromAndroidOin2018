import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.json.JSONStringer;
import java.io.*;
import java.util.*;

class JsonSimpleDemo2 {

	public static void main(String[] args) {
		//JSONObject内部封装了一个HashMap<String, String>，用于存储json对象的属性名（String类型）和属性值。
		//JSONObject构造1
		JSONObject obj = new JSONObject();
		System.out.println(obj.toString());
		obj.put("100", 1);
		obj.put("1000", 2);
		System.out.println(obj.toString());
	
		//JSONObject构造2，参数传入json格式的字符串
		JSONObject obj2 = new JSONObject(obj.toString());
		System.out.println(obj2.toString());
		
		//JSONObject属性遍历
		Iterator<String> it = obj2.keySet().iterator();
		while (it.hasNext()) {
			String key = it.next();
			System.out.println(key+" = "+(int)obj2.get(key));
		}
	}
}
