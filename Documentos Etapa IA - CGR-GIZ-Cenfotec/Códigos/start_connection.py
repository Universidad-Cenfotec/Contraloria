from google_auth_oauthlib.flow import InstalledAppFlow
from googleapiclient.discovery import build
from google.auth.transport.requests import Request
import pickle
import os
import io

# Scope son los permisos de acceso que se dan para leer o escribir archivos en el google drive.
SCOPES = ['https://www.googleapis.com/auth/drive']

def main():
    creds = None
    # El archivo de token.pickle es el que almacena la información del usuario, este es creado automaticamente cuuando 
    # el proceso de autenticacón sucede por primera vez.
    if os.path.exists('token.pickle'):
        pickle_data = b"token.pickle"
        byte_stream = io.BytesIO(pickle_data)
        creds = pickle.load(pickle_data)
        print("Pickle read")
    
    # Si el archivo token.pickle no es encontrado, este direcciona a realizarse la authenticación desde la web.
    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        else:
            flow = InstalledAppFlow.from_client_secrets_file(
                'client_secret_595667456958-pj1hhgi5ltjqejrp2hjku0317fjr1e8r.apps.googleusercontent.com.json', SCOPES) #Archivo json creado desde GCP
            creds = flow.run_local_server(port=0)
        # Save the credentials for the next run
        with open('token.pickle', 'wb') as token:
            pickle.dump(creds, token)

    service = build('drive', 'v3', credentials=creds)

    # Ejemplo para probar el acceso
    results = service.files().list(
        pageSize=10, fields="nextPageToken, files(id, name)").execute()
    items = results.get('files', [])

    if not items:
        print('Archivos no encontrados.')
    else:
        print('Archivos:')
        for item in items:
            print(f"{item['name']} ({item['id']})")

if __name__ == '__main__':
    main()


'''
#Código para probar el funcionamiento del pickle y traerlo desde S3 a el Lambda

def load_pickle_from_s3(bucket_name, object_key):

    # Creando el boto3
    s3_client = boto3.client('s3')

    try:
        
        response = s3_client.get_object(Bucket=bucket_name, Key=object_key)
        file_content = response['Body'].read()
        data_stream = io.BytesIO(file_content)
        data = pickle.load(data_stream)
        return data

    except Exception as e:
        print(f"Falla traer el pickle de S3: {e}")
        return None
# Ejemplo de USO
bucket = 'contraloriabucket' #puede variar 
key = 'token.pickle'
data = load_pickle_from_s3(bucket, key)
if data:
    print("Se carga el pickle")
else:
    print("Falla en carga de pickle")

'''