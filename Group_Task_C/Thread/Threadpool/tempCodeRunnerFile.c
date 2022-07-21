if (pool->shut_down)
    {
        pthread_mutex_unlock(&pool->mutex_pool);
        return;
    }