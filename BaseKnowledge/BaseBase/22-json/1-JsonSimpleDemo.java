import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.json.JSONStringer;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.StringReader;
import java.util.ArrayList;

class JsonUtils {

    private final static int BUFFER_SIZE = 2048;

    public static boolean LoadAndParseJson(String fileName,
                                           ArrayList<String> pkgWhiteList,
                                           String keyStr) {
        System.out.println("loadAndParseXML filename = " + fileName);
        boolean isSucceed = false;
        if (checkJsonFile(fileName)) {
            String content = readContent(fileName);
            System.out.println("loadAndParseXML content = " + content);
            try {
                String jsonContent = new JSONObject(content).getString(keyStr);
                JSONArray jsonArray = new JSONArray(jsonContent);
                System.out.println("loadAndParseXML jsonArray.length() = " + jsonArray.length());
                pkgWhiteList.clear();
                for(int i = 0; i < jsonArray.length(); i++)
                {
                    JSONObject jsonObj = jsonArray.getJSONObject(i);
                    System.out.println(jsonObj.getString("name"));
                    pkgWhiteList.add(jsonObj.getString("name"));
                }
                isSucceed = true;
            } catch (JSONException e) {
                e.printStackTrace();
                System.out.println("loadAndParseXML JSONException = " + e);
            }
            for (String pkg : pkgWhiteList) {
                System.out.println("package :" + pkg);
            }
        } else {
            System.out.println("loadAndParseXML file does not exist ");
            isSucceed = writeJsonFile(pkgWhiteList, fileName, keyStr);
        }

        return isSucceed;
    }

    public static String readContent(String fileName) {
        System.out.println("readContent fileName = " + fileName);

        StringBuilder stringBuilder = new StringBuilder();
        BufferedReader reader = null;
        try {
            System.out.println("reading...");
            reader = new BufferedReader(new FileReader(fileName));
            String tempString = null;
            while ((tempString = reader.readLine()) != null) {
                stringBuilder.append(tempString);
                System.out.println(tempString);
            }
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("IOException ...during reading" + e);
        } finally {
            if (reader != null) {
                try {
                    reader.close();
                } catch (IOException e1) {
                    System.out.println("IOException ...during closing" + e1);
                }
            }
        }
        return stringBuilder.toString();
    }

    public static boolean checkJsonFile(String fileName) {
        File file = new File(fileName);
        return file.exists();
    }

    public static boolean writeJsonFile(ArrayList<String> pkgWhiteList,
                                       String fileName,
                                       String keyStr){
        boolean isFileCreated = false;
        boolean isSucceed = false;
        File file = new File(fileName);
        System.out.println("createNewFile fileName = " + fileName);
        try {
            isFileCreated = file.createNewFile();
        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("createNewFile IOException = " + e);
        }
        System.out.println("writeJsonFile isFileCreated = " + isFileCreated);
        if (isFileCreated) {
            String jsonData = null;
            try {
                JSONArray array = new JSONArray();
                for (int i = 0; i < pkgWhiteList.size(); i++) {
                    JSONObject jsonObject = new JSONObject();
                    jsonObject.put("id", i);
                    jsonObject.put("name", pkgWhiteList.get(i));
                    array.put(jsonObject);
                }
                jsonData = new JSONStringer().object().key(keyStr).value(array).endObject().toString();
                System.out.println("str = " + jsonData);
                isSucceed = writeData(jsonData, fileName);
            } catch (JSONException e) {
                System.out.println("writeJsonFile JSONException = " + e);
                e.printStackTrace();
            }
        }
        return isSucceed;
    }

    private static boolean writeData(String jsonData, String fileName) {

        boolean isSucceed = false;
        try {
            BufferedReader reader = new BufferedReader(new StringReader(jsonData));
            BufferedWriter writer = new BufferedWriter(new FileWriter(fileName));
            int len;
            char[] buffer = new char[BUFFER_SIZE];
            while((len = reader.read(buffer)) != -1){
                writer.write(buffer, 0, len);
            }
            writer.flush();
            writer.close();
            reader.close();
            isSucceed = true;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return isSucceed;
    }
}

class JsonSimpleDemo {
	public static ArrayList<String> wkl1 = new ArrayList<String>() {
		{
			add("a.b.c");
			add("d.e.f");
			add("g.h.i");
		}
	};
	public static ArrayList<String> wkl2 = new ArrayList<String>();

	public static void main(String[] args) {

		JsonUtils.writeJsonFile(wkl1, "wk.json", "whitelist_for_wk");

		System.out.println("\n\n-----write json file end, now start read json file-----!\n\n");

		JsonUtils.LoadAndParseJson("wk.json", wkl2, "whitelist_for_wk");
		for (String d : wkl2) {
			System.out.println("data = " + d);
		}
	}
}
