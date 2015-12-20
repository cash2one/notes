
./bin/spark-submit \
  --class <main-class>
  --master <master-url> \
  --deploy-mode <deploy-mode> \
  --conf <key>=<value> \
  ... # other options
  <application-jar> [application-arguments]


----> spark-submit ����

 --master MASTER_URL
  ������spark://host:port, mesos://host:port, yarn,  yarn-cluster,yarn-client, local
  
 --deploy-mode DEPLOY_MODE
   driver����֮����client�����ڱ�����cluster�����ڼ�Ⱥ
  
 --class CLASS_NAME
  �������ƣ�������

 --name NAME
  Application����
  
 --jars JARS
  Driver�����ĵ�����jar��

 --py-files PY_FILES
  �ö��Ÿ����ķ�����PythonӦ�ó���PYTHONPATH�ϵ�.zip, .egg, .py�ļ��б�

 --files FILES
  �ö��Ÿ�����Ҫ������ÿ��executor����Ŀ¼���ļ��б�

 --properties-file FILE
  ����Ӧ�ó������Ե��ļ�·����Ĭ����conf/spark-defaults.conf

 --driver-memory MEM
  Driver����ʹ���ڴ��С

 --driver-java-options
 
 --driver-library-path
  Driver����Ŀ�·��

 --driver-class-path
  Driver�������·��

 --executor-memory MEM
  executor�ڴ��С��Ĭ��1G

 --driver-cores NUM
  Driver�����ʹ��CPU������������Spark Aloneģʽ

 --supervise
  ʧ�ܺ��Ƿ�����Driver��������Spark  Aloneģʽ

 --total-executor-cores NUM
  executorʹ�õ��ܺ�����������Spark Alone��Spark on Mesosģʽ

 --executor-cores NUM
  ÿ��executorʹ�õ��ں�����Ĭ��Ϊ1��������Spark on Yarnģʽ

 --queue QUEUE_NAME
  �ύӦ�ó�����ĸ�YARN�Ķ��У�Ĭ����default���У�������Spark on Yarnģʽ

 --num-executors NUM 
  ������executor������Ĭ����2����������Spark on Yarnģʽ

 --archives ARCHIVES
  ������Spark on Yarnģʽ
  
