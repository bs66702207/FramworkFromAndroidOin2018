/**
  序列化是指将对象的状态信息转换为可以存储或传输的形式的过程。
  在Java中创建的对象，只要没有被回收就可以被复用，但是，创建的这些对象都是存在于JVM的堆内存中，JVM处于运行状态时候，这些对象可以复用，但是一旦JVM停止，这些对象的状态也就丢失了。
  在实际生活中，需要将对象持久化，需要的时候再重新读取出来，通过对象序列化，可以将对象的状态保存为字节数组，需要的时候再将字节数组反序列化为对象。
  对象序列化可以很容易的在JVM中的活动对象和字节数组(流)之间转换，广泛用于RMI(远程方法调用)以及网络传输中。
特别注意：
  a.静态成员变量属于类不属于对象，所以不会参与序列化(对象序列化保存的是对象的“状态”，也就是它的成员变量，因此序列化不会关注静态变量)
  b.用transient关键字标记的成员变量不参与序列化(在被反序列化后，transient 变量的值被设为初始值，如 int 型的是 0，对象型的是 null)

和Serializable的对比：
  Parcelable是一个接口、用来实现序列化。与此类似的还有一个接口Serializable，这是JavaSE本身支持的，而Parcelable是android特有的。二者比较：
1. Parcelable使用起来稍复杂点，而后者使用起来非常简单。
2. Parcelable效率比Serializable高，支持Intent数据传递，也支持进程间通信(IPC)。
3. Parcelable使用时要用到一个Parcel，可以简单将其看为一个容器，序列化时将数据写入Parcel，反序列化时从中取出。
4. 在使用内存的时候，Parcelable比Serializable性能高，所以推荐使用Parcelable。Serializable在序列化的时候会产生大量的临时变量，从而引起频繁的GC。
   Parcelable不能使用在要将数据存储在磁盘上的情况，因为Parcelable在外界有变化的情况下不能很好的保证数据的持续性。尽管Serializable效率低点，但此时还是建议使用Serializable 。
*/

//frameworks/base/core/java/android/os/Parcelable.java
package android.os;

import android.os.Parcel;

public interface Parcelable {
    int PARCELABLE_WRITE_RETURN_VALUE = 1;
    int CONTENTS_FILE_DESCRIPTOR = 1;

    //功能：返回当前对象的内容描述，如果含有文件描述符，返回1
    //即CONTENTS_FILE_DESCRIPTOR
    //几乎所有情况都会返回0
    int describeContents();

    /**
      * 序列化功能由writeToParcel完成，最终通过Parcel的一系列Write方法完成
    */
    //功能：将当前对象写入序列化结构中，其中flags标识有两种值，0或1
    //为1时标识当前对象需要作为返回值返回，不能立刻释放资源，即PARCELABLE_WRITE_RETURN_VALUE
    //不过几乎所有情况都为0
    void writeToParcel(Parcel var1, int var2);

    //反序列过程：必须实现Parcelable.Creator接口，并且对象名必须为CREATOR  
    //读取Parcel里面数据时必须按照成员变量声明的顺序，Parcel数据来源上面writeToParcel方法，读出来的数据供逻辑层使用 
    public interface ClassLoaderCreator<T> extends Parcelable.Creator<T> {
        T createFromParcel(Parcel var1, ClassLoader var2);
    }

    public interface Creator<T> {
        T createFromParcel(Parcel var1);

        T[] newArray(int var1);
    }
}

//使用范例
package com.home.testparcelable;

import android.os.Parcel;
import android.os.Parcelable;

//Student:
public class Student implements Parcelable {
    private int id;
    private String name;

    public Student() {
        super();
    }

    public Student(int id, String name) {
        super();
        this.id = id;
        this.name = name;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        // 序列化过程：必须按成员变量声明的顺序进行封装
        dest.writeInt(id);
        dest.writeString(name);
    }

    // 反序列过程：必须实现Parcelable.Creator接口，并且对象名必须为CREATOR
    // 读取Parcel里面数据时必须按照成员变量声明的顺序，Parcel数据来源上面writeToParcel方法，读出来的数据供逻辑层使用
    public static final Parcelable.Creator<Student> CREATOR = new Creator<Student>() {

        @Override
        public Student createFromParcel(Parcel source) {
            return new Student(source.readInt(), source.readString());
        }

        @Override
        public Student[] newArray(int size) {
            return new Student[size];
        }
    };

}

//MainActivity:
package com.home.testparcelable;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MainActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        Button btn = (Button) findViewById(R.id.main_btn);
        btn.setOnClickListener(new OnClickListener() {

            @Override
            public void onClick(View arg0) {
                Intent in = new Intent(MainActivity.this, SecondActivity.class);
                in.putExtra("stu", new Student(1, "张三"));
                startActivity(in);
            }
        });
    }
}

//SecondActivity:
package com.home.testparcelable;

import android.app.Activity;
import android.os.Bundle;

public class SecondActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Student stu = getIntent().getParcelableExtra("stu");
        System.out.println("id:" + stu.getId());
        System.out.println("name:" + stu.getName());
    }
}


