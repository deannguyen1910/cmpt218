Resource managements 
Program control 
Protection - Kernel do itsself 


event-driven 



syscall lib 
System calls 
Interrupts 
Signals 


Why it reuiqes privillege to switch between modes >? user mode and kernel mode 
bubbling c

How Kernel security chekc works?  Hamming code correction 

gh auth login -p ssh -w

   Setting Things Up for gitHub                                                                                       
                                                                                                                      
  (Navigation: Type  q  to exit. Type  b  to go back to the previous page. Type  <Space>  to go to                    
  the next page. Type  j  to scroll down by one line. Type  k  to scroll up by one line. You probably                 
  want to remember these keys now since you need to scroll up and down this document as you read it.)                 
                                                                                                                      
  ## Account Creation                                                                                                 
                                                                                                                      
  The first thing you need to do is to make sure you have an account on GitHub. Go to  github.com  and                
  create an account if you don't have one yet. If you have a GitHub account already, you do not need                  
  to create a new one.                                                                                                
                                                                                                                      
  ## Setting Up an SSH Key                                                                                            
                                                                                                                      
  You now need to set up something called an SSH key so that you can conveniently access your GitHub                  
  code repositories (or repos in short).                                                                              
                                                                                                                    
  • Do not use this terminal to follow the instructions. Keep this terminal open to view the rest of                  
  the instructions. Instead, open another terminal instance, ssh into this virtual machine again,                     
  and work from there. Depending on which terminal emulator you use, you can open an entirely new                     
  window or just a tab. For example, if you use Windows Terminal, iTerm2, etc., they all support                      
  tabbing.                                                                                                            
  • Enter  gh auth login -p ssh -w  on the command line to add your SSH key to your GitHub account.                   
  The command asks a few questions, which you can answer as follows.                                                  
    • Generate a new SSH key to add to your GitHub account? Press  <Enter> .                                          
    • Enter a passphrase for your new SSH key (Optional) Press  <Enter> .                                             
    • Title for your SSH key. Press  <Enter>  for the default name or give a custom name for                          
    your SSH key, e.g., cmpt201.                                                                                      
    • After that, it asks you to copy a one-time code. Copy it or just remember it. You just need to                  
    type it in on your browser. Then, as the instructions say, press  <Enter>  to open                                
     github.com . If the browser does not open automatically, manually go to                                          
    https://github.com/login/device, enter the one-time code                                                          
    there, and authorize access to your GitHub account. It may take a bit to finish authorization.                    
                                                                                                                      
                                                                                                                      
   Next Steps                                                                                                         
                                                                                                                      
  Exit this document, enter  glow -p ASGN.md , and follow the instructions there.                                     
                                                                                                                    
  (Navigation: Type  q  to exit. Type  b  to go back to the previous page. Type  <Space>  to go to                    
  the next page. Type  j  to scroll down by one line. Type  k  to scroll up by one line.)                             
