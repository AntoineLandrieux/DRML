# **Welcome to DRML!**

![DMRLicon](https://raw.githubusercontent.com/AntoineLandrieux/DRML/main/resources/drml24.png) SHELL Language


## **Contribute**

DRML - 2022 LANDRIEUX Antoine


## **External libraries used by DRML**

- **For windows©**

  - libgcc_s_dw2-1.dll
  - libstdc++\-6.dll

- **For linux©**
  - none

## **Exemple**

    ~ This is a comment
    
    namespace app :
        $start=1;
        $stop=0;
    end;
    
    if $app::start != $app::stop exec :
        out "START\n";
        &app::start=0;
        if $app::start == $app::stop exec :
            out "STOP";
        else :
            out "CONTINUE";
        end;
    end;
    
    exit;

