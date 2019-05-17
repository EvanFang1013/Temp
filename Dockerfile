FROM tensorflow/tensorflow:1.10.0-gpu-py3_v2_sshd

# env variable
ENV DEBIAN_FRONTEND noninteractive
ENV SSH_PASSWORD demo



#ssh configuration
RUN apt-get install -y openssh-server
RUN mkdir -p /var/run/sshd
RUN echo 'root:password' | chpasswd
RUN sed -i 's/PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config
RUN sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd
RUN sed -i 's/#PasswordAuthentication/PasswordAuthentication/' /etc/ssh/sshd_config
RUN echo "ClientAliveInterval 30" >> /etc/ssh/sshd_config
RUN echo "export PATH=$PATH" >> /etc/profile && \
    echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib/nvidia:/usr/lib/x86_64-linux-gnu" >> /etc/profile && \
    echo "ldconfig" >> /etc/profile

ENV NOTVISIBLE "in users profile"







# TensorBoard
EXPOSE 6006
# IPython
EXPOSE 8888
# SSH
EXPOSE 22


#run as deamon
CMD ["/usr/sbin/sshd","-D"]

