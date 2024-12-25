# templates directory
## Three subdirectories
**components_only** directory: template for making libraries
**applications_only** directory: for making applications
**headers_only** directory: for installing header only hpps

        templates/     
        ├── components_only/   
        │   └── components/   
        ├── applications_only/   
        │   └── applications/   
        └── headers_only/   
            └── header_only/   
  
# Usage
1. Each subdirectory can be used independently. See README in each subdirectory.
   
2. Also usable in combination: see followings.

# In combination

1. Based on the **components_only** directory:  
Copy the **applications_only/applications/** and the **headers_only/header_only/** directory into the components_only directory.  

        components_only/   
        ├── components/   
        ├── applications/   
        ├── header_only/   
        └── ...    


2. Based on the **applications_only** directory:  
Copy the **headers_only/header_only/** directory to the applications_only directory.

        applications_only/   
        ├── applications/   
        ├── header_only/   
        └── ...    

(as of 2024-12-25 11:59:46)